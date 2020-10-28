/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:26:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/28 09:56:15 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*last;
}				t_list;

typedef struct	s_hash_content
{
	void			*value;
	char			*key;
	struct s_hash_content	*next;
	struct s_hash_content	*last;
}				t_hash_content;


typedef struct	s_hash_table
{
	t_hash_content *table;
	unsigned int size;
	unsigned int used_size;
	unsigned int expanding_size;
}				t_hash_table;

#endif