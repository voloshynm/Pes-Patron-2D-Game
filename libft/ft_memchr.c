/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:54:41 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/06 16:55:04 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*t;

	t = (unsigned char *)s;
	while (n > 0)
	{
		if (*t == (unsigned char)c)
			return (t);
		t++;
		n--;
	}
	return (NULL);
}
