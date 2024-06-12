/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:10:01 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/16 17:10:02 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	parse_format(t_data *data);

static void	parse_flags(t_data *data)
{
	while (is_in(*data->s, "-+ #0"))
	{
		if (*data->s == '-')
			data->fmt.is_left = true;
		else if (*data->s == '+')
			data->fmt.is_plus = true;
		else if (*data->s == ' ')
			data->fmt.is_space = true;
		else if (*data->s == '#')
			data->fmt.is_hash = true;
		else if (*data->s == '0')
			data->fmt.is_zero_pad = true;
		++data->s;
	}
}

static int	my_atoi(t_data *data)
{
	int	value;

	value = 0;
	while (is_in(*data->s, "0123456789"))
		value = (value * 10) + (*data->s++ - '0');
	return (value);
}

static void	parse_value(t_data *data, int *value)
{
	if (*data->s == '*')
	{
		*value = va_arg(data->ap, int);
		++data->s;
		return ;
	}
	*value = my_atoi(data);
}

int	parse_format(t_data *data)
{
	data->fmt.precision = -1;
	parse_flags(data);
	parse_value(data, &data->fmt.width);
	if (*data->s == '.' && *(++data->s))
		parse_value(data, &data->fmt.precision);
	if (!is_in(*data->s, "cspdiuxX%"))
		return (PARSE_ERROR);
	else
	{
		data->fmt.specifier = *data->s;
		if (is_in(data->fmt.specifier, "diu"))
			data->fmt.base = 10;
		else if (is_in(data->fmt.specifier, "xXp"))
		{
			data->fmt.base = 16;
			if (data->fmt.specifier == 'X')
				data->fmt.is_x_upper = true;
		}
		++data->s;
	}
	return (OK);
}
