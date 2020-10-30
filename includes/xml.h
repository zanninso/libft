/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:04:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/30 21:30:12 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef XML_H
# define XML_H

#include <fcntl.h>
# include "libft.h"
#define XMLTAGOPEN 1
#define XMLTAGCLOSE 2
#define XMLVALUE 3

enum{
	XML_NOERR,XML_MALLOC_ERR,XML_BADCLOSE_ERR,XML_NOROOT_ERR,XML_ROOTEND,XML_NOOPEN_ERR
};

typedef struct	s_xml_lexer
{
	char            *value;
	int 	type;
    int    value_len;
}          t_xml_lexer ;

typedef union u_tag_value
{ 
    int integer;
    float decimal;
	double real;
	long bigint;
    char *string;
}			t_tag_value;

typedef struct	s_xml_tag
{
	char            *name;
	t_list 			*nodes;
	t_list			*attributes;
    t_tag_value    	value;
}         		t_xml_tag;

typedef struct	s_dtd
{
	char            *name;
	t_list 			*nodes;
	t_list			*attributes;
    t_tag_value    	value;
}         		t_dtd;

t_list *read_and_tokenizexml(int fd);
t_xml_tag *xml_modeling(t_list *tokens);

#endif