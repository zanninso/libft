/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dtd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:28:31 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/01 22:55:20 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml.h"

int valide_pcdata(char *str, const char *cmp, size_t *col, size_t line)
{
    col[0] += 7;
    if (ft_isinstr(str[*col], cmp))
    {
        col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
        ft_printf("%s\n", &str[*col]);
        return (1);
    }
    ft_printf("invalide splitter after node name line:%lu, col:%lu\n", line, *col);
    return (0);
}

int valide_name(char *str, const char *cmp, size_t *col, size_t line)
{
    int i = 0;

    ft_printf("-------------------->%s|%d\n", str + *col, *col);
    *col += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
    if (ft_strnequ("#PCDATA", &str[*col], 7))
        return (valide_pcdata(str, cmp, col, line));
    while (str[*col])
    {
        ft_printf(":%c::%s:\n", str[*col], cmp);
        if (ft_isinstr(str[*col], cmp) && i > 0)
        {
            col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
            ft_printf("%s\n", &str[*col]);
            return (1);
        }
        if (!ft_isalnum(str[*col]))
        {
            ft_printf("node name accept just aphabet line:%lu, col:%lu\n", line, *col);
            return (0);
        }
        col[0]++;
        i = 1;
    }
    ft_printf("invalide tag close ll line:%lu, col:%lu\n", line, *col);
    return (0);
}

int valide_rule_splitter(char *str, size_t *col, size_t line, char *splitter)
{
    if (*splitter == '\0' && (str[*col] == '|' || str[*col] == ','))
    {
        *splitter = str[*col];
    }
    else if (*splitter == '\0' || str[*col] != *splitter)
    {
        ft_printf("invalide node splitter line:%lu, col:%lu\n", line, *col);
        return (0);
    }
    col[0]++;
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
        if (str[*col] != '(' && !valide_name(str, " |,+*?)", col, line))
            return (0);
        if (str[*col] == '(' && !valide_rule(str, col, line))
            return (0);
        col[0] += ft_isinstr(str[*col], "*+?");
        col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
        if (str[*col] == ')' && (col[0] += 1))
        {
            col[0] += ft_isinstr(str[*col], "*+?");
            col[0] += (ft_skip_chars(&str[*col], " ", NULL) - (str + *col));
            ft_printf("valide rule : %s\n", str + *col);
            return (1);
        }
        if (!valide_rule_splitter(str, col, line, &splitter))
            return (0);
    }
    ft_printf("No bracket close line:%lu, col:%lu\n", line, *col);
    return (0);
}

int valide_restrictions(char *str, size_t *c, size_t l)
{
    c[0]++;
    while (str[*c])
    {
        *c = (ft_skip_chars(&str[*c], " ", NULL) - (&str[*c]));
        if (!valid_min_max(str, c, l))
            return (0);
        else if (!valid_type(str, c, l))
            return (0);
        else if (!valid_enum(str, c, l))
            return (0);
        else
        {
            ft_printf("Invalide restriction line:%lu, col:%lu\n", l, *c);
            return (0);
        }
        if (str[*c] == ')')
        {
            *c = (ft_skip_chars(&str[*c], " ", NULL) - (&str[*c]));
            return (1);
        }
    }
    ft_printf("No bracket close line:%lu, col:%lu\n", l, *c);
    return (0);
}

int valid_dtd_element(char *str, size_t line)
{
    size_t col;

    col = (ft_skip_chars(str, " ", NULL) - (str)) + 10;
    if (!ft_strnequ("<!ELEMENT ", str + (col - 10), 10))
    {
        ft_printf("invalide tag type line:%lu, col:%lu", line, col);
        return (0);
    }
    if (!valide_name(str, " (", &col, line))
        return (0);
    if (str[col] != '(')
    {
        ft_printf("No element-content line:%lu, col:%lu", line, col);
        return (0);
    }
    if (!valide_rule(str, &col, line))
        return (0);
    if (str[col] == '(' && !valide_restrictions(str, &col, line))
        return (0);
    if (str[col] != '>')
    {
        ft_printf("invalide tag close line:%lu, col:%lu", line, col);
        return (0);
    }
    return (1);
}