/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:39:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/26 13:58:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml.h"

void opentag()
{
	
}

void closetag()
{
	
}

void check_value()
{
	
}

t_xml *validate_xml(t_list *tokens, t_xml_schema *dtd)
{
	t_list *tag_queue;
	t_xml_lexer *tmp;
	t_xml_data *xml;
	while (tokens)
	{
		tmp = tokens->content;
		if(tmp->type == XMLTAGOPEN)
			opentag()
		else if(tmp->type == XMLTAGCLOSE)
			closetag();
		else 
			check_value();
	}
	return xml;
}