/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_dom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:39:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/29 14:50:08 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml.h"

void opentag(t_list **tag_queue, t_xml_lexer *token)
{
	ft_printf("\topen tag : %s\n", token->value);
	t_xml_tag tag;
	tag.name = ft_strsub(token->value, 1, token->value_len - 2);
	tag.value.string = NULL;
	tag.nodes = NULL;
	// tag.attributes = get_attributes(token);
	ft_lstpush(tag_queue, ft_lstnew(&tag, sizeof(t_xml_tag)));
}

void closetag(t_list **tag_queue, t_xml_lexer *token)
{
	// t_xml_tag *tag;
	t_xml_tag *parent_tag;
	t_list *poped_node;

	ft_printf("\tclose tag : %s\n", token->value);
	token = NULL;
	poped_node = ft_lstpop(tag_queue);
	// if(!ft_strnequ(tag->name, token->value + 1, token->value_len - 2))
	// 	return ;
	parent_tag = (*tag_queue)->content;
	ft_lstenqueue(&parent_tag->nodes, poped_node);
	// if((tmp = hash_find(parent_tag->nodes, tag->name, tag, size)))
	// {
	// 	ft_lstenqueue(&tmp, tag);
	// 	// hash_update(parent_tag->nodes, tag->name, tmp, size);
	// }
	// else
	// 	hash_insert(parent_tag->nodes, tag->name, tag, 1);
}

void check_value(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag *parent_tag;
	t_xml_tag tag;
	
	ft_printf("\tvalue tag : %s\n", token->value);
	tag.name = ft_strdup("#PCDATA");
	tag.value.string = ft_strdup(token->value);
	tag.nodes = NULL;	
	parent_tag = (*tag_queue)->content;
	ft_lstenqueue(&parent_tag->nodes, ft_lstnew(&tag, sizeof(tag)));
}

t_xml_tag *xml_modeling(t_list *tokens)
{
	t_list *tag_queue;
	t_xml_lexer *tmp;
	// int error;

	tag_queue = NULL;
	while (tokens)
	{
		tmp = tokens->content;
		if(tmp->type == XMLTAGOPEN)
			opentag(&tag_queue, tmp);
		else if(tag_queue && tmp->type == XMLVALUE)
			check_value(&tag_queue, tmp);
		else if(tmp->type == XMLTAGCLOSE && tag_queue && tag_queue->next)
			closetag(&tag_queue, tmp);
		else
			break;
		ft_lstdequeue(&tokens, ft_memdel);
	}
	return (tag_queue->content);
}