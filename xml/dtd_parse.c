/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:56:33 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/30 14:55:29 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void get_rules(char *str)
{
    while (str)
    {
    }
}

parse_element()
{
    
}

parse_value_constraint()
{
    
}

parse_attribute_list()
{
    
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