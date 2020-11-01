/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dtd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:28:31 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/01 14:42:12 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml.h"

int valide_name(char *str, const char *cmp, size_t *col, size_t line)
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
        col[0]++;
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
        col[0]++;
    }
    else if (*splitter == '\0' || str[*col] != *splitter)
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
    col[0]++;
    while (str[*col])
    {
        col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
        if (str[*col] == '(' && !valide_rule(str, col, line))
            return (0);
        else if (!valide_name(&str[*col], " |,+*?", col, line))
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


int valide_restrictions(char *str, size_t *c, size_t l)
{
    c[0]++;
    while (str[*c])
    {
        *c = (ft_skip_chars(&str[*c], " ", NULL) - (&str[*c]));
        if(!valid_min_max(str, c, l))
            return(0);
        else if(!valid_type(str, c, l))
            return(0);
        else if(!valid_enum(str, c, l))
            return(0);
        else
        {
            ft_printf("Invalide restriction line:%ul, col:%ul\n", l, *c);
            return(0);
        }
        if(str[*c] == ')')
        {
            *c = (ft_skip_chars(&str[*c], " ", NULL) - (&str[*c]));
            return (1);
        }
    }
    ft_printf("No bracket close line:%ul, col:%ul\n", l, *c);
    return (0);
}

int valid_dtd_element(char *str, size_t line)
{
    size_t col;
    
    col = (ft_skip_chars(str, " ", NULL) - (str)) + 9;
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
    return(1);
}