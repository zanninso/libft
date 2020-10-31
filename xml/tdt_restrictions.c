/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tdt_restrictions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:33:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/31 23:32:42 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int valid_min_max(char *str, size_t *col, size_t line)
{
    int dot;

    dot = 0;
    if (!ft_strnequ("min=", &str[*col], 4) || ft_strnequ("max=", &str[*col], 4))
        return (1);
    col[0] += 4;
    while (str[*col])
    {
        if (ft_isdigit(str[*col]))
            col[0]++;
        else if (str[*col] == '.' && dot == 0)
        {
            dot = 1;
            col[0]++;
        }
        else if (str[*col] == ';')
            return (1);
        else
            break;
    }
    ft_printf("Invalid character line:%ul, col:%ul", line, col);
    return (0);
}

static valid_type(char *str, size_t *col, size_t line)
{
    static const char** types = {"string;","integer;","decimal;","boolean;",0};
    int i;

    if (!ft_strnequ("type=", &str[*col], 5))
        return (1);
    col[0] += 5;
    i = 0;
    while(types[i])
    {
        if (ft_strnequ(types[i], &str[*col], ft_strlen(types[i])))
        {
            col[0] += ft_strlen(types[i]);
            return(1);
        }
        i++;
    }
    ft_printf("Invalid type line:%ul, col:%ul", line, col);
    return (0);
}

static valid_enum(char *str, size_t *col, size_t line)
{
    if (!ft_strnequ("enum=", &str[*col], 5))
        return (1);
    col[0] += 5;
    while ()
    {
    }
}