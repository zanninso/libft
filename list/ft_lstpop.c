/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:46:27 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/28 22:46:31 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **lst)
{
    t_list *tmp;
    
	if (lst && *lst)
	{
        tmp = *lst;
        *lst = (*lst)->next;
        tmp->next = NULL;
        tmp->last = NULL;
        return (tmp);
	}
    return (NULL);
}
