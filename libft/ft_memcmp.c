/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:10:14 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/06 17:10:31 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n-- > 0)
	{
		if (*tmp_s1 != *tmp_s2)
			return (*tmp_s1 - *tmp_s2);
		tmp_s1++;
		tmp_s2++;
	}
	return (0);
}
