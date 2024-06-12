/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:44:00 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/02 18:49:50 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	i = 1;
	if (n == 0)
		return (0);
	while (i < n && *tmp_s1 && *tmp_s2 && *tmp_s1 == *tmp_s2)
	{
		tmp_s1++;
		tmp_s2++;
		i++;
	}
	return ((int)(*tmp_s1 - *tmp_s2));
}
