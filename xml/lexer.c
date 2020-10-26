/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:48:45 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/26 13:49:24 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "xml.h"

static t_xml_lexer xmlexer_get_tag(char **line)
{
	char *tmp;
	char *tmp2;
	t_xml_lexer node;

	node.type = (line[0][1] == '/' ? XMLTAGCLOSE : XMLTAGOPEN);
	tmp = *line;
	*line = ft_skip_unitl_char(tmp, ">", NULL);
	*line += 1;
	node.value_len = *line - tmp;
	tmp = ft_strsub(tmp,0, node.value_len);
	node.value = tmp;
	
	return (node);
}

static t_xml_lexer xmlexer_get_value(char **line)
{
	char *tmp;
	t_xml_lexer node;

	tmp = *line;
	*line = ft_skip_unitl_char(tmp, "<", NULL);
	node.type = XMLVALUE;
	node.value_len = *line - tmp;
	node.value = ft_strsub(tmp, 0, node.value_len);
	return (node);
}

t_list *add_to_xmlexer(t_list *tokens, char *line)
{
	t_xml_lexer xmlnode;

	while (*line)
	{
		line = ft_skip_chars(line, NULL, ft_iswhitespace);
		if (*line)
		{
			if (*line == '<')
				xmlnode = xmlexer_get_tag(&line);
			else
				xmlnode = xmlexer_get_value(&line);
			ft_lstenqueue(&tokens, ft_lstnew(&xmlnode, sizeof(t_xml_lexer)));
		}
	}
	return tokens;
}

t_list *read_and_tokenizexml(int fd)
{
	t_list *tokens;
	char *line;

	tokens = NULL;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		tokens = add_to_xmlexer(tokens, line);
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	return tokens;
}