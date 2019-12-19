/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstenqueue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:44:52 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/19 00:49:05 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstenqueue(t_list *list, t_list *new)
{
    if(new && list)
    {
        list->last->next = new;
        list->last = new;
        return (list);
    }
    return (NULL);
}
