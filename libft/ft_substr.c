/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:39:12 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/11 13:39:34 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*subs;
	char const	*s_offset;
	char		*subs_start;
	size_t		s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		len = 0;
		start = s_len;
	}
	else if (len > s_len - start)
		len = s_len - start;
	subs = malloc(len + 1);
	if (!subs)
		return (NULL);
	subs_start = subs;
	s_offset = s + start;
	while (*s_offset && len-- > 0)
		*subs++ = *s_offset++;
	*subs = '\0';
	return (subs_start);
}
