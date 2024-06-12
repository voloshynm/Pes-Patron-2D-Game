/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:45:21 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/27 17:45:23 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	create_list_b(t_list **list, int fd);
void	add_list_b(t_list **list, char *buffer);
char	*get_line_b(t_list **list);
void	copy_next_line_b(t_list **list, char *next_line, int line_len);
int		get_len_to_newline_char_b(t_list *list);
int		has_new_line_char_b(t_list *list);
void	clean_list_b(t_list **list, t_list *clean_node);
void	clean_node_b(t_list **list, int i);
t_list	*find_last_node_b(t_list *list);

#endif
