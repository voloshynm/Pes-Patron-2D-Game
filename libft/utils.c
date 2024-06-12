/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:16:37 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/16 17:16:38 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

bool	is_in(char c, const char *s)
{
	if (s == NULL)
		return (false);
	while (*s)
	{
		if (*s == c)
			return (true);
		s++;
	}
	return (false);
}

int	my_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_pf(const char *s)
{
	char	*dup;
	char	*start;
	char	*s_l;
	size_t	l;

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

static char	ft_tolower_c(char c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

char	get_base_symbol(long int index, bool is_upper)
{
	char	*upper;
	char	c;

	upper = ft_strdup_pf("0123456789ABCDEF");
	if (is_upper)
		c = upper[index];
	else
		c = ft_tolower_c(upper[index]);
	free (upper);
	return (c);
}
