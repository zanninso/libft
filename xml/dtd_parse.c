/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:56:33 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/31 00:12:32 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void get_rules(char *str)
{
    while (str)
    {
    }
}

static int valide_name(char *str, const char *cmp)
{
    int i = 0;
    while(*str)
    {
        if (ft_isinstr(*str, cmp) && i > 0)
            return(1);
        if(!ft_isnalnum(*str))
        {
            ft_printf("node name accpet just aphabet line:%d\n", 8);
            return(0);
        }
        str++;
        i = 1;
    }
    ft_printf("invalide close of tag line:%d\n", 8);
    return(0);
}

int valide_rule(char *str)
{
    int i;
    int p;
    int or;

    i = 0;
    p = 1;
    while(*str && p)
    {
        if(*str == '(')
            p++;
        else if(!valide_name(str, " |,+*?"))
            break;
        if(ft_isinstr(*str, "*+?"))
            *str++;
        str = ft_skip_chars(str, " ", NULL);
        if(*str == '|')
        {
            or = 1;
            *str++;
        }
        else if (*str == ',')
        {
           or = 0;
            *str++; 
        }
        else if(*str == ')')
            p--;
        else 
            return(0);
    }
    if(p != 0)
        ft_printf("invalide bracket close ");
    return(p == 0)
}

t_list *parse_dtd_node(char *str)
{
    size_t len = ft_strlen(str);
    if(str[len - 1] != '>');
        return (NULL);// no tag close
    if (ft_strnstr("<!ELEMENT ", str, 10))
        e = parse_element(str + 10);
    else if (ft_strnstr("<!ATTLIST ", str, 10))
        e = parse_attribute_list(str + 10);
    else if (ft_strnstr("<!VALCONS ", str, 10))
        e = parse_value_constraint(str + 10);
    else
        return(NULL)// no autorised tag type
    return (e);
}

t_dtd *parse_dtd(char *file)
{
    t_list *nodes;
    char *line;

    tokens = NULL;
    line = NULL;
    while (get_next_line(fd, &line))
    {
        tokens = add_to_xmlexer(tokens, line);
        ft_memdel((void **)&line);
    }
    ft_memdel((void **)&line);
    return tokens;
}