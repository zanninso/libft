/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 07:21:19 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/19 01:20:43 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_translate(char *str, const char *from, const char *to)
{
	int	i;

	if (!str || !from || !to)
		return (str);
	while (*str)
	{
		i = 0;
		while (from[i])
		{
			if (*str == from[i])
			{
				*str = to[i];
				break ;
			}
			i++;
		}
		str++;
	}
	return(str);
}
