/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:56:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/03 00:25:18 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"

bool or_splitter(t_list *childs, t_dtd *dtd)
{
    t_list *elm;
    elm = dtd->content;
    while(elm)
    {
        
    }
}

bool dtd_validate(t_xml_tag *tag, t_hash_table *dtd, const char *tag_name)
{
    t_list tmp_tag;
    if(!ft_strequ(tag->name, tag_name))
    {
        ft_printf("Invalide tag name line: col:");
        return(0);
    }
    while ()
    {
        if()
       dtd_validate()
    }
    
}