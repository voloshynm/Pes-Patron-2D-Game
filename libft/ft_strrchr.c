/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:19:12 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/02 17:19:36 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*start;

	start = s;
	if (c > 255 || c < 0)
		return ((char *)start);
	if (s == NULL)
		return (NULL);
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s)
		s++;
	while (s >= start)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
