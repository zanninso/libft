/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_dom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:39:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/04 15:38:28 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml.h"

int opentag(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag tag;
	t_list *new;
	
	if(token->value[token->value_len - 1] != '>' || token->value_len < 3)
		return(ft_printf(OPEN_TAG_ERR ,token->line, token->col));
	tag.name = ft_strsub(token->value, 1, token->value_len - 2);
	tag.value = NULL;
	tag.nodes = NULL;
	tag.col = token->col;
	tag.line = token->line;
	// tag.attributes = get_attributes(token);	
	new = ft_lstnew(&tag, sizeof(t_xml_tag));
	ft_lstpush(tag_queue, new);
	return(1);
}

int closetag(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag *tag;
	t_xml_tag *parent_tag;
	t_list *poped_node;
	char	*tmp;

	if(!tag_queue || !*tag_queue)
		return(ft_printf(NO_TAG_TO_CLOSE,token->line, token->col) * 0);
	tag = (*tag_queue)->content;
	ft_printf("#### %s | %s | %d\n",tag->name,token->value+2, token->value_len);
	tmp = ft_strsub(token->value, 2, token->value_len - 3);
	if(!ft_strequ(tag->name, tmp) || token->value[token->value_len - 1] != '>')
	{
		free(tmp);
		return(ft_printf(INV_TAG_CLOS, tag->name, token->value, token->line, token->col) * 0);
	}
	free(tmp);
	ft_printf("#### ok\n");
	if((*tag_queue)->next == NULL)
		return(2);
	poped_node = ft_lstpop(tag_queue);
	parent_tag = (*tag_queue)->content;
	ft_lstenqueue(&parent_tag->nodes, poped_node);
	return(1);
}

int check_value(t_list **tag_queue, t_xml_lexer *token)
{
	t_xml_tag *parent_tag;
	t_xml_tag tag;
	t_list *new;
	
	if(!tag_queue || !*tag_queue)
		return(ft_printf(NO_TAG_FOR_VAL,token->line, token->col) * 0);
	tag.name = ft_strdup("#PCDATA");
	tag.value = ft_strdup(token->value);
	tag.nodes = NULL;
	tag.col = token->col;
	tag.line = token->line;
	new =  ft_lstnew(&tag, sizeof(t_xml_tag));
	parent_tag = (*tag_queue)->content;
	ft_lstenqueue(&parent_tag->nodes, new);
	return(1);
}

static t_xml_tag *manage_status(t_list *tokens,t_list *tag_queue,int status)
{
	t_xml_tag *tag;
	t_xml_lexer *tmp;

	if(status == 2 && tokens == NULL)
	{
		tag = tag_queue->content;
		free(tag_queue);
		return(tag);
	}
	if (status == 2)
	{
		tmp = (t_xml_lexer *)tokens->content;
		ft_printf(ELEM_AFTER_ROOT,tmp->line, tmp->col);
	}
	if(status == 1)
	{
		tag = tag_queue->content;
		ft_printf(NO_TAG_CLOSE, tag->name);
	}
	//manage_error(tokens, tag_queue, status);
	//free tag_queue
	// ft_lstdel(&tokens);
	return(NULL);
}

t_xml_tag *xml_modeling(t_list *tokens)
{
	t_list *tag_queue;
	t_xml_lexer *tmp;
	int status;

	tag_queue = NULL;
	status = 1;
	while (tokens && status == 1)
	{
		tmp = tokens->content;
		if(tmp->type == XMLTAGOPEN)
			status = opentag(&tag_queue, tmp);
		else if(tmp->type == XMLTAGCLOSE)
			status = closetag(&tag_queue, tmp);
		else if(tmp->type == XMLVALUE)
			status = check_value(&tag_queue, tmp);
		if(status)
			ft_lstdequeue(&tokens, ft_memdel);
	}
	return (manage_status(tokens, tag_queue, status));
}