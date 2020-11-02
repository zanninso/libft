/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_unitl_chars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:41:59 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/02 14:56:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

const char	*ft_strdup_unitl_chars(const char *str, const char *compare)
{
    int n;
    char *new;

    n = 0;
	while (str && str[n] && !ft_isinstr(str[n], compare))
		n++;
    if(n > 0 && (new = malloc(sizeof(char) * (n+1))))
        return (ft_strncpy(str, new, n));
	return (NULL);
}