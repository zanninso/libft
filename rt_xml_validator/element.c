/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:16:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/04 20:46:05 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"

static char *get_val(t_list *nodes)
{
    t_xml_tag *tag;
    if(nodes->next)
        return(NULL);
    return(((t_xml_tag *)nodes->content)->value);
}

bool rt_valid_vec(t_xml_tag *tag)
{
    const char* tab[] = {"x", "y", "z", NULL};
    t_list *nodes;
    t_xml_tag *tmp;
    int i;

    nodes = tag->nodes;
    while (nodes)
    {
        if (i == 3)
            return (ft_printf("additional tag here\n") * 0);
        tmp = nodes->content;
        if (!ft_strequ(tab[i], tmp->name))
            return (ft_printf("invalid tag name ") * 0);
        if (!ft_isdouble(get_val(tmp->nodes)))
            return (ft_printf("invalide values\n") * 0);
        nodes = nodes->next;
        i++;
    }
    return (1);
}

bool rt_valid_enum(t_xml_tag *tag, const char *enums)
{
    char **tab;
    bool is_in_arr;

    tab = ft_strsplit(enums, ",");
    is_in_arr = ft_str_in_arr(get_val(tag->nodes), tab);
    ft_free_2d_tab(tab);
    if (!is_in_arr)
        ft_printf("invalid value\n");
    return (is_in_arr);
}

bool rt_valid_cut_exist(t_xml_tag *tag)
{
    t_list *nodes;
    t_xml_tag *tmp;
    int i;

    nodes = tag->nodes;
    while (nodes)
    {
        if (i == 2)
            return (ft_printf("additional tag here\n") * 0);
        tmp = nodes->content;
        if (!ft_strequ("limit_xyz", tmp->name))
            return (ft_printf("invalid tag name ") * 0);
        if (!rt_valid_vec(tmp))
            return (0);
        nodes = nodes->next;
        i++;
    }
    return (1);
}


bool rt_valid_vec(t_xml_tag *tag);
bool rt_valid_cut_exist(t_xml_tag *tag);
bool rt_valid_enum(t_xml_tag *tag, const char *enums);