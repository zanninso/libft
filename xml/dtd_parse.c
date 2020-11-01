/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:56:33 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/02 00:06:17 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"

parse_content_element(line)
{
    
}

parse_value_restrictions()
{
    
}

t_dtd get_dtd_tag(char *line)
{
    char *tmp;
    char *name;
    
    line = ft_skip_chars(line, " ", NULL);
    tmp = ft_skip_unitl_char(line, " ", NULL);
    *name = ft_strsub(line, 0, tmp - line);
    line = ft_skip_chars(tmp, " ", NULL);
    parse_content_element();
    line = ft_skip_chars(line, " ", NULL);
    parse_value_restrictions();
}

t_dtd *parse_dtd(char *file)
{
    t_list *nodes;
    char *line;
    size_t line_count;
	int fd;

	fd = open("rt.dtd", O_RDONLY);
	ft_printf("fd : %d\n",fd);
    line = NULL;
    line_count = 0;
    while (get_next_line(fd, &line) > 0)
    {
		ft_printf("line:|%s|\n",line);
        if(!valid_dtd_element(line, line_count))
        {
            return (NULL);
        }
        get_dtd_tag(line + TAG_TYPE_LEN);
        ft_memdel((void **)&line);
        line_count++;
    }
    ft_memdel((void **)&line);
	ft_printf("file is okay\n");
	return(0);
}