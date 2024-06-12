/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:06:46 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/12 16:06:53 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_itoa(int n);

char	*safe_malloc(size_t size)
{
	char	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	unsigned int	i;
	char			a[15];
	char			*s;

	i = 0;
	a[i++] = '\0';
	if (n == 0)
		a[i++] = '0';
	if (n < 0)
		num = (unsigned int)(-n);
	else
		num = (unsigned int)(n);
	while (num > 0)
	{
		a[i++] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		a[i++] = '-';
	s = safe_malloc(i);
	num = 0;
	while (i > 0)
		s[num++] = a[--i];
	return (s);
}
