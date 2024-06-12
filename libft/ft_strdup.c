/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:30:02 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/06 18:30:24 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	char	*start;
	char	*s_l;
	int		l;

	l = 0;
	s_l = (char *)s;
	while (*s_l++)
		l++;
	dup = malloc(l + 1);
	if (dup == NULL)
		return (NULL);
	start = dup;
	s_l = (char *)s;
	while (*s_l)
		*dup++ = *s_l++;
	*dup = '\0';
	return (start);
}
