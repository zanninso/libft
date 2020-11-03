/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:56:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/03 12:00:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"

bool valid_elm_cardinality(t_list *child, t_list *dtd)
{
    if(child == NULL && dtd == NULL)
        return(1);
    if(dtd == NULL)
        return(0);
    while (true)
    {
    }
    
}

bool valid_element(t_list *childs, t_dtd *dtd)
{
    t_list *elm;
    t_dtd_element_content *content;
    int i;

    elm = dtd->content;
    content = elm->content;
    i = 0;
    if(content->name)
    {
    }
    if(valid_elm_cardinality())
}

bool dtd_validate(t_xml_tag *tag, t_hash_table *dtd, const char *tag_name)
{
    static t_hash_table *static_dtd;
    t_list tmp_tag;

    if(dtd)
        static_dtd = dtd;
    if(!ft_strequ(tag->name, tag_name))
    {
        ft_printf("Invalide tag name line: col:");
        return(0);
    }
    while ()
    {
       dtd_validate()
    }
    
}