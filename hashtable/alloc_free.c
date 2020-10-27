/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:25:08 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/27 23:54:02 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

free_hash_table(t_hash_table **tab, )
{
    if(tab && *tab)
    {
        free_hash_content((*tab)->table, free_fun);
        free(*tab);
        *tab = NULL;
    }
}

free_hash_content(t_hash_content, )
{
    
}

