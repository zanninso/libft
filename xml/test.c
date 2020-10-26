/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:56:57 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/26 13:12:07 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# include "xml.h"

int main(int ac, char **av)
{
    int fd;
    t_list *lst;
    t_xml_lexer *tmp;
    if((fd = open(av[1], O_RDONLY)) > 0)
    {
        ft_printf("start tokenization\n");
        lst = read_and_tokenizexml(fd);
        ft_printf("end tokenization\n");
        while (lst)
        {
            tmp = (t_xml_lexer *)lst->content;
            ft_printf("value:%s | type:%d | value len:%d\n",tmp->value, tmp->type, tmp->value_len);
            lst = lst->next;
        }
        
    }
}