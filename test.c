/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:56:57 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/01 20:37:09 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xml.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void print_xml(t_xml_tag *tag,int level)
{
	t_list *tmp;
	int i = 0; 
	while (i++ < level)
			printf("\t");
	printf("%s : ", tag->name);
	tmp = tag->nodes;
	if(tmp)
	{
		printf("\n");
		while(tmp)
		{
			print_xml(tmp->content, level + 1);
			tmp = tmp->next;
		}
	}
	else
		printf("%s\n",tag->value.string);
}

int main()
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
            ft_printf("error error error\n");
            exit(0);
        }
        ft_memdel((void **)&line);
        line_count++;
    }
    ft_memdel((void **)&line);
	ft_printf("file is okay\n");
	return(0);
}

// int main(int ac, char **av)
// {
//     int fd;
//     t_list *lst;
// 	t_list *tokens;
//     t_xml_lexer *tmp;
//     t_xml_tag *root;
//     if((fd = open(av[1], O_RDONLY)) > 0)
//     {
//         ft_printf("start tokenization\n");
//         lst = tokens = read_and_tokenizexml(fd);
//         while (lst)
//         {
//             tmp = (t_xml_lexer *)lst->content;
//             ft_printf("value:%s | type:%d | value len:%d\n",tmp->value, tmp->type, tmp->value_len);
//             lst = lst->next;
//         }
//         ft_printf("end tokenization\n");
//         root = xml_modeling(tokens);
// 		print_xml(root, 0);
//     }
// }