/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:56:33 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/02 14:56:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"

char *get_tdt_elm_cntnt_name(char **line)
{
    char *tmp;
    char *name;

    *line = ft_skip_chars(*line, " ", NULL);
    tmp = ft_skip_unitl_char(*line, " *+?),|", NULL);
    name = ft_strsub(*line, 0, tmp - *line);
    *line  = tmp;
    return(name);
}

t_dtd_element_content parse_content_element(char **line)
{
    t_dtd_element_content element;
    t_dtd_element_content ret;

    ft_bzero(&ret, sizeof(t_dtd_element_content));
    while (true)
    {
        ft_bzero(&element, sizeof(t_dtd_element_content));
        if(**line != '(')
            element.name = get_tdt_elm_cntnt_name(line);
        if(**line == '(')
            element = parse_content_element(line);
        if(ft_isinstr(**line, "*?+"))
            element.cardinality = line[0][0]++;
        *line = ft_skip_chars(*line, " ", NULL);
        if(**line == ')')
        {
            line[0][0]++;
            if(ft_isinstr(**line, "*?+"))
                ret.cardinality = line[0][0]++;
            return(ret);
        }
        ret.splitter = line[0][0]++;
        ft_lstenqueue(&ret.elements, ft_lstnew(&element, sizeof(t_dtd_element_content)));
    }
    return(ret);
}

t_dtd_restriction parse_value_restrictions(char **line)
{
    t_dtd_restriction restriction;
    char *tmp;
    
    line[0][0]++;
    while (**line)
    {
        if(**line  == ';')
            line[0][0]++;
        if(ft_strnequ("min=", *line, 4))
            restriction.min = ft_atoi(*line + 4);
        if(ft_strnequ("max=", *line, 4))
            restriction.max = ft_atoi(*line + 4);
        if(ft_strnequ("type=", *line, 5))            
            restriction.type = ft_strsub(*line, 5, ft_skip_unitl_char(*line, ";", 0) - *line );
        if(ft_strnequ("enum=", *line, 5))
        {
            tmp  = ft_skip_unitl_char(*line, ";", NULL);
            *tmp = '\0';
            restriction.enumeration = ft_strsplit(*line + 5, ",");
            *tmp = ';';
        }
        *line = ft_skip_unitl_char(*line, ";", NULL);
    }
    return(restriction);
}

t_dtd *get_dtd_tag(char **line)
{
    t_dtd *dtd_tag;
    char *tmp;

    dtd_tag = ft_memalloc(sizeof(t_dtd));
    *line = *line + TAG_TYPE_LEN;  
    *line = ft_skip_chars(*line, " ", NULL);
    tmp = ft_skip_unitl_char(*line, " ", NULL);
    dtd_tag->name = ft_strsub(*line, 0, tmp - *line);
    *line = ft_skip_chars(tmp, " ", NULL);
    dtd_tag->content = parse_content_element(line);
    *line = ft_skip_chars(*line, " ", NULL);
    dtd_tag->restriction = parse_value_restrictions(line);
    return(dtd_tag);
}

t_dtd *parse_dtd(char *file)
{
    // t_hash_table *nodes;
    char *line;
    size_t line_count;
    int fd;

    fd = open(file, O_RDONLY);
    ft_printf("fd : %d\n", fd);
    line = NULL;
    line_count = 0;
    while (get_next_line(fd, &line) > 0)
    {
        ft_printf("line:|%s|\n", line);
        if (!valid_dtd_element(line, line_count))
        {
            return (NULL);
        }
        get_dtd_tag(&line);
        ft_memdel((void **)&line);
        line_count++;
    }
    ft_memdel((void **)&line);
    ft_printf("file is okay\n");
    return (0);
}