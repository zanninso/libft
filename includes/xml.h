/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:04:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/26 13:20:29 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef XML_H
# define XML_H

#include <fcntl.h>
# include "libft.h"
#define XMLTAGOPEN 1
#define XMLTAGCLOSE 2
#define XMLVALUE 3

typedef struct	s_xml_lexer
{
	char            *value;
	int 	type;
    int    value_len;
}          t_xml_lexer ;

t_list *read_and_tokenizexml(int fd);

#endif