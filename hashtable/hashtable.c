/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:12:26 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/02 14:56:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long hash_key(const char *key)
{
    unsigned long hash = 0;

    while (*key)
    {
        hash += (unsigned long)*key;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return (hash);
}

int t_hash_table(t_hash_table *tab, const char *key, void *value, int expand)
{
    unsigned int pos;
    t_hash_content *tmp;

    if (tab->used_size == tab->size)
        if (!expand || !resize_hashtable(tab))
            return (0);
    pos = hash_key(key) % tab->size;
    if (tab[pos].key)
    {
        if ((tmp = ft_memalloc(sizeof(t_hash_content))))
        {
            tmp->key = key;
            tmp->value = value;
            if (tab->table[pos].last)
                ;
            tab->table[pos].last->next = tmp;
            tab->table[pos].last = tmp;
            if (!tab->table[pos].next)
                tab->table[pos].next = tmp;
            tab->used_size++;
        }
        return (tmp != NULL);
    }
    tab->table[pos].key = key;
    tab->table[pos].value = value;
    return (tab->used_size++);
}

void *hash_find(t_hash_table *tab, const char *key)
{
    unsigned int pos;
    t_hash_content *tmp;

    pos = hash_key(key) % tab->size;
    if (!tab->table[pos].next || ft_strequ(key, tab->table[pos].key))
        return (tab->table[pos].value);
    tmp = tab->table[pos].next;
    while (tmp)
    {
        if (ft_strequ(key, tmp->key))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

resize_hashtable_end(t_hash_table *tab, t_hash_table *newtab, int noerror)
{
    if (!noerror)
    {
        free_hash_table(newtab);
        return (0);
    }
    if (!newtab)
        return(0);
    free_hash_content(tab->table, NULL);
    ft_memcpy(tab, new_tab, sizeof(t_hash_table));
    free(new_tab);
    return (1);
}

int resize_hashtable(t_hash_table *tab)
{
    unsigned int i;
    t_hash_content *tmp;
    t_hash_table newtab;
    unsigned int size;
    int noerror;

    size = tab->size + tab->expanding_size;
    i = 0;
    noerror = 1;
    if ((newtab = new_hash_table(size, tab->expanding_size)))
        while (i < size && noerror)
        {
            if (tab->table[i].key)
            {
                noerror = hash_insert(newtab, tab->table[i].key, tab->table[i].value, 0);
                if ((tmp = tab->table[i].next))
                    while (tmp && noerror)
                    {
                        noerror = hash_insert(newtab, tmp->key, tmp->value, 0);
                        tmp = tmp->next;
                    }
            }
            i++;
        }
    return (resize_hashtable_end(tab, newtab, noerror));
}