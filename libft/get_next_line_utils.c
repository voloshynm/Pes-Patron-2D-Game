/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:45:03 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/27 17:45:05 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	has_new_line_char_b(t_list *list)
{
	char	*buf;

	if (list == NULL || list->str == NULL)
		return (0);
	while (list)
	{
		buf = list->str;
		while (*buf)
		{
			if (*buf == '\n')
				return (1);
			buf++;
		}
		list = list->next;
	}
	return (0);
}

void	clean_node_b(t_list **list, int i)
{
	t_list	*clean_node;
	t_list	*last_node;
	int		j;

	if (list == NULL || *list == NULL)
		return ;
	last_node = *list;
	last_node = find_last_node_b(last_node);
	clean_node = malloc(sizeof(t_list));
	clean_node->str = malloc(BUFFER_SIZE - i + 1);
	j = 0;
	while (last_node->str[i])
		clean_node->str[j++] = last_node->str[i++];
	clean_node->str[j] = '\0';
	clean_node->next = NULL;
	clean_list_b(list, clean_node);
}

void	clean_list_b(t_list **list, t_list *clean_node)
{
	t_list	*tmp;

	if (list == NULL || *list == NULL)
		return ;
	while (*list != NULL)
	{
		tmp = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = tmp;
	}
	if (clean_node->str[0])
		*list = clean_node;
	else
	{
		free(clean_node->str);
		free(clean_node);
	}
}

int	get_len_to_newline_char_b(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
				return (++len);
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

t_list	*find_last_node_b(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
