/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:31:22 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/02 21:52:41 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_comp;
	char	*little_comp;
	size_t	len_little;

	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	while (*big && len >= len_little)
	{
		big_comp = (char *)big;
		little_comp = (char *)little;
		while (*little_comp != '\0' && *little_comp == *big_comp)
		{
			little_comp++;
			big_comp++;
		}
		if (*little_comp == '\0')
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
