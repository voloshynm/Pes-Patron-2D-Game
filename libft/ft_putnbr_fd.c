/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:38:17 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/12 15:38:27 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	unsigned int	i;
	unsigned int	a[50];

	if (n == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		num = (unsigned int)(-n);
	}
	else
		num = (unsigned int)(n);
	i = 0;
	while (num > 0)
	{
		a[i++] = num % 10;
		num = num / 10;
	}
	while (i-- > 0)
		ft_putchar_fd(a[i] + '0', fd);
}
