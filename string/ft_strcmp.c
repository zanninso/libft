/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:06:28 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/06/19 22:18:26 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s, const char *s2)
{
	while (*s && *s2 && (*s - *s2) == 0)
	{
		s2++;
		s++;
	}
	return (*s != *s2 ? (unsigned char)*s - (unsigned char)*s2 : 0);
}
