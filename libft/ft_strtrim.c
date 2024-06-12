/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:36:52 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/11 15:37:06 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char		*trim;
	char		*trim_start;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = s1;
	while (*start && is_set(*start, set))
		start++;
	end = start;
	while (*end)
		end++;
	while (end > start && is_set(*(end - 1), set))
		end--;
	trim = malloc(end - start + 1);
	if (trim == NULL)
		return (NULL);
	trim_start = trim;
	while (start < end)
		*trim_start++ = *start++;
	*trim_start = '\0';
	return (trim);
}
