/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:52:07 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/02 21:21:13 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;
	char	*dst_end;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = 0;
	dst_end = dst + d_len;
	while (*src && d_len + 1 + i < size)
	{
		*dst_end++ = *src++;
		i++;
	}
	if (d_len < size - 1)
		*dst_end = '\0';
	if (size < d_len)
		return (s_len + size);
	return (d_len + s_len);
}
