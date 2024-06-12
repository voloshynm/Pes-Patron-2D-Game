/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:35:33 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/16 19:35:35 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//function to put char c, n times, and cnt into data->chars_written
void	putchar_n(t_data *data, int n, int c )
{
	if (n <= 0)
		return ;
	while (n--)
	{
		write(1, &c, 1);
		++data->chars_written;
	}
}

//function to put char with left/right padding for width 
void	render_char(t_data *data, int c)
{
	int		width;

	width = data->fmt.width;
	if (width > 1)
	{
		if (c == '%')
			putchar_n(data, 1, c);
		else if (data->fmt.is_left)
		{
			putchar_n(data, 1, c);
			putchar_n(data, width - 1, ' ');
		}
		else
		{
			putchar_n(data, width - 1, ' ');
			putchar_n(data, 1, c);
		}
	}
	else
		putchar_n(data, 1, c);
}

//function to put string, n characters, and cnt into data->chars_written
void	putstr_n(t_data *data, int n, char *s )
{
	int	i;

	if (n <= 0)
		return ;
	i = n;
	while (i-- && *s)
	{
		write(1, s, 1);
		++data->chars_written;
		s++;
	}
}

//function to put char with left/right padding for width 
void	render_str(t_data *data, char *s)
{
	int	chars_to_print;

	if (s == NULL && (data->fmt.precision > 5 || data->fmt.precision <= 0))
		s = "(null)";
	else if (s == NULL)
		s = "";
	if (data->fmt.precision >= 0 && data->fmt.precision <= my_strlen(s))
		chars_to_print = data->fmt.precision;
	else
		chars_to_print = my_strlen(s);
	if (data->fmt.width > 0)
	{
		if (data->fmt.is_left)
		{
			putstr_n(data, chars_to_print, s);
			putchar_n(data, data->fmt.width - chars_to_print, ' ');
		}
		else
		{
			putchar_n(data, data->fmt.width - chars_to_print, ' ');
			putstr_n(data, chars_to_print, s);
		}
	}
	else
		putstr_n(data, chars_to_print, s);
}
