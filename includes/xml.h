/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 12:04:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/11/02 16:56:21 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef XML_H
# define XML_H
#include "libft.h"
#include <fcntl.h>
#define XMLTAGOPEN 1
#define XMLTAGCLOSE 2
#define XMLVALUE 3
#define TAG_TYPE_LEN 10

enum{
	XML_NOERR,XML_malloc_ERR,XML_BADCLOSE_ERR,XML_NOROOT_ERR,XML_ROOTEND,XML_NOOPEN_ERR
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


typedef struct	s_dtd_restriction
{
	long		min;
	long		max;
	char		*type;
	char		**enumeration;
}         		t_dtd_restriction;

typedef struct	s_dtd_element_content
{
	char            	*name;
	char				cardinality;
	char				splitter;
	t_list 				*elements;
}         		t_dtd_element_content;

typedef struct	s_dtd
{
	char					*name;
	t_dtd_element_content	content;
	t_list					*attributes;
    t_dtd_restriction		restriction;
}         		t_dtd;

t_list *read_and_tokenizexml(int fd);
t_xml_tag *xml_modeling(t_list *tokens);

int		valid_min_max(char *str, size_t *col, size_t line);
int		valid_type(char *str, size_t *col, size_t line);
int		valid_enum(char *str, size_t *col, size_t line);
int		valid_dtd_element(char *str, size_t line);
t_dtd	*parse_dtd(char *file);



#endif