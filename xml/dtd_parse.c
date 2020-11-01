/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:56:33 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/01 11:35:05 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int valide_name(char *str, const char *cmp, size_t *col, size_t line)
{
    int i = 0;
    while (str[*col])
    {
        if (ft_isinstr(str[*col], cmp) && i > 0)
        {
            col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
            return (1);
        }
        if (!ft_isnalnum(str[*col]))
        {
            ft_printf("node name accept just aphabet line:%ul, col:%ul\n", line, *col);
            return (0);
        }
        *col++;
        i = 1;
    }
    ft_printf("invalide tag close line:%ul, col:%ul\n", line, *col);
    return (0);
}

int valide_rule_splitter(char *str, size_t *col, size_t line, char *splitter)
{
    if (*splitter == '\0' && (str[*col] == '|' || str[*col] == ','))
    {
        *splitter = str[*col];
        *col++;
    }
    else if (*splitter == '\0' || str[*col] != splitter)
    {
        ft_printf("invalide node splitter line:%ul, col:%ul\n", line, *col);
        return (0);
    }
    return (1);
}

int valide_rule(char *str, size_t *col, size_t line)
{
    char splitter;

    splitter = '\0';
    *col++;
    while (str[*col])
    {
        col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
        if (str[*col] == '(' && !valide_rule(str, col))
            return (0);
        else if (!valide_name(&str[*col], " |,+*?"))
            return (0);
        col[0] += ft_isinstr(str[*col], "*+?");
        col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
        if (*str == ')')
        {
            col[0] += ft_isinstr(str[*col], "*+?");
            col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
            return (1);
        }
        if (!valide_rule_splitter(str, col, line, &splitter))
            return (0);
    }
    ft_printf("No bracket close line:%ul, col:%ul\n", line, *col);
    return (0);
}

int validate_tdt_element(char *str, size_t line)
{
    size_t col;

    col = (ft_skip_chars(&str[col], " ", NULL) - (str + col)) + 9;
    if (!ft_strnstr("<!ELEMENT", str, 9))
    {
        ft_printf("invalide tag type line:%ul, col:%ul", line, col);
        return (0);
    }
    if(!valide_name(str, " (", &col, line))
        return (0);
    if(str[col] != '(')
    {
        ft_printf("No element-content line:%ul, col:%ul", line, col);
        return (0);
    }
    if(!valide_rule(str, &col, line))
        return(0);
    if(str[col] == '(' && !valide_restrictions(str, &col, line))
        return(0);
    if(str[col] != '>')
    {
        ft_printf("invalide tag close line:%ul, col:%ul", line, col);
        return (0);
    }
    return(1)
}

t_dtd *parse_dtd(char *file)
{
    t_list *nodes;
    char *line;
    size_t line_count;

    tokens = NULL;
    line = NULL;
    line_count = 0;
    while (get_next_line(fd, &line))
    {
        if(!valid_dtd_element(line ))
        {
            ft_printf("error error error\n");
            exit(0);
        }
        ft_memdel((void **)&line);
        line_count++;
    }
    ft_memdel((void **)&line);
    return tokens;
}