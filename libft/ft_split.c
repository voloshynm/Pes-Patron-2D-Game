/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:49:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/11 19:50:01 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	splits_cnt(char const *s, char c)
{
	char	*buf;
	int		split_cnt;

	buf = (char *)s;
	split_cnt = 0;
	while (*buf)
	{
		if (*buf && *buf == c)
			while (*buf && *buf == c)
				buf++;
		if (*buf && *buf != c)
		{
			while (*buf && *buf != c)
				buf++;
			split_cnt++;
		}
	}
	return (split_cnt);
}

char	*ft_get_split_str(char const *s, char c)
{
	char	*str;
	char	*split_str;
	char	*split_str_start;
	int		split_len;

	str = (char *)s;
	while (*str && *str != c)
		str++;
	split_len = str - s;
	if (split_len == 0)
		return (NULL);
	str = (char *)s;
	split_str = malloc(split_len + 1);
	split_str_start = split_str;
	if (split_str == NULL)
		return (NULL);
	while (*str && split_len-- > 0)
		*split_str++ = *str++;
	*split_str = '\0';
	return (split_str_start);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	**temp;
	char	*buf;

	res = (char **)malloc(sizeof(char *) * (splits_cnt(s, c) + 1));
	if (res == NULL)
		return (NULL);
	temp = res;
	while (*s)
	{
		if (c == '\0' || *s != c)
		{
			buf = ft_get_split_str(s, c);
			if (buf != NULL)
			{
				*temp++ = buf;
				s += ft_strlen(buf);
				continue ;
			}
		}
		s++;
	}
	*temp = NULL;
	return (res);
}
