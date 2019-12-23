/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstenqueue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:44:52 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/21 14:08:50 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list *ft_lstenqueue(t_list **list, t_list *new)
{
    if(new && list && *list)
    {
        if((*list)->last)
            (*list)->last->next = new;
        else
            (*list)->next = new;
        (*list)->last = new;
        return ((*list));
    }
    else if(new && list)
    {
        *list = new;
        return ((*list));
    }
    return (NULL);
}
