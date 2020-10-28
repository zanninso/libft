/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:25:08 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/28 12:51:00 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void free_hash_table(t_hash_table **tab, void (*del)(void **))
{
    if (tab && *tab)
    {
        free_hash_content((*tab)->table, (*tab)->size, del);
        free(*tab);
        *tab = NULL;
    }
}

void free_hash_content(t_hash_content **table, unsigned int size, void (*del)(void **))
{
    unsigned int i;
    t_hash_content *tmp;
    t_hash_content *to_free;

    i = 0;
    while (++i < size)
        if (tab->table[i].key)
        {
            tmp = table[0][i - 1].next;
            while (tmp)
            {
                if(del)
                {
                    del(tmp->value);
                    ft_memdel(tmp->key);
                }
                to_free = tmp;
                tmp = tmp->next;
                free(to_free);
            }
            del(table[0][i - 1].value);
            ft_memdel(table[0][i - 1].key);    
        }
    ft_memdel((void **)table);
}

t_hash_table *new_hash_table(unsigned int size, unsigned int expnading_size)
{
    t_hash_table *table;

    table = ft_memalloc(sizeof(t_hash_table) * size);
    if (table)
    {
        table->size = size;
        table->expanding_size = expnading_size;
        if ((table->table = ft_memalloc(sizeof(t_hash_content) * size)))
            return (table);
        free(table);
    }
    return (NULL);
}
