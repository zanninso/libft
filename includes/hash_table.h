/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:26:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/10/27 21:42:47 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

typedef struct	s_hash_content
{
	void	*value;
	char	*key;
	t_hash_content	*next;
	t_hash_content	*last;
}				t_hash_content;


typedef struct	s_hash_table
{
	t_hash_content *table;
	unsigned int size;
	unsigned int used_size;
	unsigned int expanding_size;
}				t_hash_table;

#endif