/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_dom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:39:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/02 14:56:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml.h"

int opentag(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag tag;
	t_list *new;
	
	if(!(tag.name = ft_strsub(token->value, 1, token->value_len - 2)))
		return(XML_malloc_ERR);
	tag.value.string = NULL;
	tag.nodes = NULL;
	// tag.attributes = get_attributes(token);	
	if(!(new = ft_lstnew(&tag, sizeof(t_xml_tag))))
	{
		free(tag.name);
		return(XML_malloc_ERR);
	}
	ft_lstpush(tag_queue, new);
	return(XML_NOERR);
}

int closetag(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag *tag;
	t_xml_tag *parent_tag;
	t_list *poped_node;

	if(!tag_queue || !*tag_queue)
		return(XML_BADCLOSE_ERR);
	poped_node = ft_lstpop(tag_queue);
	tag = poped_node->content;
	if(!ft_strnequ(tag->name, token->value + 1, token->value_len - 2))
		return(XML_BADCLOSE_ERR);
	if(!*tag_queue)
		return(XML_ROOTEND);
	parent_tag = (*tag_queue)->content;
	ft_lstenqueue(&parent_tag->nodes, poped_node);
	return(XML_NOERR);
}

int check_value(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag *parent_tag;
	t_xml_tag tag;
	t_list *new;
	
	if(!tag_queue || !*tag_queue)
		return(XML_NOOPEN_ERR);
	tag.name = ft_strdup("#PCDATA");
	tag.value.string = ft_strdup(token->value);
	tag.nodes = NULL;
	new =  ft_lstnew(&tag, sizeof(t_xml_tag));
	if(!tag.name || !tag.value.string || !new)
	{
		free(tag.name);
		free(tag.value.string);
		ft_lstdel(&new);
		return(XML_malloc_ERR);
	}
	parent_tag = (*tag_queue)->content;
	ft_lstenqueue(&parent_tag->nodes, new);
	return(XML_NOERR);
}

static t_xml_tag *manage_status(t_list *tokens,t_list *tag_queue,int status)
{
	t_xml_tag *tag;
	if(status == XML_ROOTEND)
	{
		if(!tokens)
		{
			tag = tag_queue->content;
			free(tag_queue);
			return(tag);
		}
		status = XML_NOROOT_ERR;
	}
	//manage_error(tokens, tag_queue, status);
	//free tag_queue
	ft_lstdel(&tokens);
	return(NULL);
}

t_xml_tag *xml_modeling(t_list *tokens)
{
	t_list *tag_queue;
	t_xml_lexer *tmp;
	int status;

	tag_queue = NULL;
	status = 0;
	while (tokens && status == 0)
	{
		tmp = tokens->content;
		if(tmp->type == XMLTAGOPEN)
			status = opentag(&tag_queue, tmp);
		else if(tmp->type == XMLTAGCLOSE)
			status = closetag(&tag_queue, tmp);
		else if(tmp->type == XMLVALUE)
			status = check_value(&tag_queue, tmp);
		if(status == 0)
			ft_lstdequeue(&tokens, ft_memdel);
	}
	return (manage_status(tokens, tag_queue, status));
}