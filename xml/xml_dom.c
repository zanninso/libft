/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_dom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:39:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/28 14:54:23 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml.h"

void opentag(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag tag;
	tag.name = ft_strsub(token->value, 1, token->value_len - 1);
	tag.value.string = NULL;
	tag.nodes = NULL;
	// tag.attributes = get_attributes(token);
	// ft_lstpush();
	ft_lstadd(tag_queue, ft_lstnew(&tag, sizeof(tag)));
}

void closetag(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag *tag;
	t_xml_tag *parent_tag;
	t_list *poped_node;
	//if is correct tag close
	tmp = ft_lstpop(tag_queue);
	tag = poped_node->content;
	free(tmp);
	parent_tag = (*tag_queue)->next->content;
	ft_lstenqueue(&parent_tag->nodes, tag);
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
	
	tag.name = ft_strsub("#PCDATA");
	tag.value.string = ft_strdup(token->value);
	tab.nodes = NULL;	
	parent_tag = (*tag_queue)->content;
	ft_lstenqueue(&parent_tag->nodes, t_lstnew(&tag, sizeof(tag));
}

t_xml_tag *xml_modeling(t_list *tokens, t_xml_schema *dtd)
{
	t_list *tag_queue;
	t_xml_lexer *tmp;
	t_xml_data *xml;
	while (tokens)
	{
		tmp = tokens->content;
		if(tmp->type == XMLTAGOPEN)
			opentag(&tag_queue, tmp);
		else if(tmp->type == XMLVALUE)
			check_value(&tag_queue, tmp);
		else if(tmp->type == XMLTAGCLOSE && tag_queue->next)
			closetag(&tag_queue, tmp);
		else
			break;
		ft_lstdequeue(tokens, ft_memdel);
	}
	return (tag_queue->content);
}