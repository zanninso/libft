/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:56:33 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/02 20:01:11 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"

char *get_tdt_elm_cntnt_name(char **line)
{
    char *tmp;
    char *name;

    // ft_printf("get_tdt_elm_cntnt_name---\n");
    *line = ft_skip_chars(*line, " ", NULL);
    tmp = ft_skip_unitl_char(*line, " *+?),|", NULL);
    name = ft_strsub(*line, 0, tmp - *line);
    *line = tmp;
    // ft_printf("%s|%s\n---------------------------------\n", name, *line);
    return (name);
}

t_dtd_element_content parse_content_element(char **line)
{
    t_dtd_element_content element;
    t_dtd_element_content ret;

    line[0]++;
    ft_bzero(&ret, sizeof(t_dtd_element_content));
    while (true)
    {
        ft_bzero(&element, sizeof(t_dtd_element_content));
        if (**line != '(')
            element.name = get_tdt_elm_cntnt_name(line);
        else if (**line == '(')
            element = parse_content_element(line);
        ft_isinstr(**line, "*?+") ? (element.cardinality = *line[0]++) : 0;
        ft_lstenqueue(&ret.elements, ft_lstnew(&element, sizeof(t_dtd_element_content)));
        *line = ft_skip_chars(*line, " ", NULL);
        if (**line == ')')
        {
            line[0]++;
            (ft_isinstr(**line, "*?+")) ? (ret.cardinality = *line[0]++) : 0;
            return (ret);
        }
        ret.splitter = *line[0]++;
    }
    return (ret);
}

t_dtd_restriction parse_value_restrictions(char **line)
{
    t_dtd_restriction restriction;
    char *tmp;

    line[0]++;
    while (**line)
    {
        if (**line == ';')
            line[0]++;
        if (ft_strnequ("min=", *line, 4))
            restriction.min = ft_atoi(*line + 4);
        else if (ft_strnequ("max=", *line, 4))
            restriction.max = ft_atoi(*line + 4);
        else if (ft_strnequ("type=", *line, 5))
            restriction.type = ft_strsub(*line, 5, ft_skip_unitl_char(*line, ";", 0) - *line);
        else if (ft_strnequ("enum=", *line, 5))
        {
            tmp = ft_skip_unitl_char(*line, ";", NULL);
            *tmp = '\0';
            restriction.enumeration = ft_strsplit(*line + 5, ",");
            *tmp = ';';
        }
        *line = ft_skip_unitl_char(*line, ";", NULL);
    }
    return (restriction);
}

t_dtd *get_dtd_tag(char *line)
{
    t_dtd *dtd_tag;
    char *tmp;

    // ft_printf("start parsing dtd\n");
    dtd_tag = ft_memalloc(sizeof(t_dtd));
    // ft_printf("allocation\n");
    line = line + TAG_TYPE_LEN;
    line = ft_skip_chars(line, " ", NULL);
    tmp = ft_skip_unitl_char(line, " ", NULL);
    dtd_tag->name = ft_strsub(line, 0, tmp - line);
    // ft_printf("get name |%s| \n", dtd_tag->name);
    line = ft_skip_chars(tmp, " ", NULL);
    // ft_printf("skip space |%s| \n", line);
    dtd_tag->content = parse_content_element(&line);
    // ft_printf("parse element content \n", dtd_tag->name);
    line = ft_skip_chars(line, " ", NULL);
    // dtd_tag->restriction = parse_value_restrictions(line);
    return (dtd_tag);
}

void print_char(char c, int n)
{
    char *tab;

    tab = MALLOC(n + 1);
    ft_memset(tab, c, n);
    tab[n] = 0;
    ft_printf("%s",tab);
    free(tab);
}
void print_tag_content(t_dtd_element_content tag, int level)
{ 
    t_list *tmp;
    print_char('\t',level);
    ft_printf("name : %s\n",tag.name);
    print_char('\t',level);
    ft_printf("cadinality : %c\n",tag.cardinality);
    print_char('\t',level);
    ft_printf("splitter : %c\n",tag.splitter);
    print_char('\t',level);
    ft_printf("elements :\n");
    tmp = tag.elements;
    while(tmp)
    {
        print_tag_content(*((t_dtd_element_content *)tmp->content), level + 1);
        tmp = tmp->next;
    }
}

t_dtd *parse_dtd(char *file)
{
    // t_hash_table *nodes;
    char *line;
    size_t line_count;
    int fd;
    t_dtd *tmp;

    fd = open(file, O_RDONLY);
    // ft_printf("fd : %d\n", fd);
    line = NULL;
    line_count = 0;
    while (get_next_line(fd, &line) > 0)
    {
        // ft_printf("line:|%s|\n", line);
        if (!valid_dtd_element(line, line_count))
        {
            return (NULL);
        }
        tmp = get_dtd_tag(line);
        ft_printf("tag name : %s\n", tmp->name);
        print_tag_content(tmp->content, 1);
        ft_memdel((void **)&line);
        line_count++;
    }
    ft_memdel((void **)&line);
    ft_printf("file is okay\n");
    return (0);
}