/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:50:14 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/16 15:50:16 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	null_data(t_data *data)
{
	long unsigned int	i;

	data->fmt.padding_zeros = 0;
	data->fmt.padding_spaces = 0;
	data->fmt.is_left = 0;
	data->fmt.is_plus = 0;
	data->fmt.is_space = 0;
	data->fmt.is_hash = 0;
	data->fmt.is_zero_pad = 0;
	data->fmt.width = 0;
	data->fmt.precision = -1;
	data->fmt.is_negative = 0;
	data->fmt.is_abs = 0;
	data->fmt.base = 0;
	data->fmt.num_len = 0;
	data->fmt.is_x_upper = 0;
	i = 0;
	while (i < sizeof(data->fmt.num))
	{
		data->fmt.num[i] = '\0';
		i++;
	}
}

static int	init_data(t_data *data, const char *format)
{
	null_data(data);
	data->s = format;
	data->chars_written = 0;
	return (OK);
}

int	print_format(t_data *data)
{
	char	specifier;

	specifier = data->fmt.specifier;
	if (specifier == '%')
		render_char(data, '%');
	else if (specifier == 'c')
		render_char(data, va_arg(data->ap, int));
	else if (specifier == 's')
		render_str(data, va_arg(data->ap, char *));
	else if (is_in(specifier, "dipxXu"))
		render_num(data);
	return (OK);
}

//initialize variadic function with va_start and init_data in struct 
int	ft_printf(const char *format, ...)
{
	t_data	data;

	va_start(data.ap, format);
	if (init_data(&data, format))
		return (MALLOC_ERROR);
	while (*data.s)
	{
		if (*data.s == '%' && *(++data.s))
		{
			if (parse_format(&data))
			{
				write(1, "Parsing Error!", 14);
				return (PARSE_ERROR);
			}
			print_format(&data);
			null_data(&data);
		}
		else
		{
			write(1, data.s, 1);
			++data.chars_written;
			++data.s;
		}
	}
	return (data.chars_written);
}
