/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:44:42 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/27 17:44:50 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	copy_next_line_b(t_list **list, char *next_line, int line_len)
{
	int		i;
	int		j;
	t_list	*node;

	if (list == NULL || *list == NULL)
		return ;
	node = *list;
	j = 0;
	while (node && j < line_len)
	{
		i = 0;
		while (node->str[i] && j < line_len)
			next_line[j++] = node->str[i++];
		node = node->next;
	}
	next_line[j++] = '\0';
	clean_node_b(list, i);
}

char	*get_line_b(t_list **list)
{
	int		line_len;
	char	*next_line;

	if (list == NULL || *list == NULL)
		return (NULL);
	line_len = get_len_to_newline_char_b(*list);
	next_line = malloc(line_len + 1);
	if (next_line == NULL)
		return (NULL);
	copy_next_line_b(list, next_line, line_len);
	return (next_line);
}

void	add_list_b(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->str = buffer;
	new_node->next = NULL;
	last_node = find_last_node_b(*(list));
	if (last_node == NULL)
		*(list) = new_node;
	else
		last_node->next = new_node;
}

void	create_list_b(t_list **list, int fd)
{
	int		char_read;
	char	*buffer;

	if (list == NULL)
		return ;
	while (!has_new_line_char_b(*(list)))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free (buffer);
			return ;
		}
		else
			buffer[char_read] = '\0';
		add_list_b(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[4096];
	char			*next_line;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list_b(&(list[fd]), fd);
	if (list[fd] == NULL)
		return (NULL);
	next_line = get_line_b(&(list[fd]));
	return (next_line);
}
