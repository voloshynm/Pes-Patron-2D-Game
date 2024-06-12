/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:58:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/19 16:58:39 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	itoa_base(t_data *data, t_num values)
{
	t_num	tmp;
	t_num	remainder;
	char	a[64];
	int		i;

	i = 0;
	tmp = values;
	if (data->fmt.is_negative && !data->fmt.is_abs)
	{
		tmp.nb = -(tmp.nb);
		data->fmt.is_abs = true;
	}
	while (tmp.unb >= data->fmt.base)
	{
		remainder.unb = tmp.unb % data->fmt.base;
		tmp.unb = tmp.unb / data->fmt.base;
		a[i++] = get_base_symbol(remainder.unb, data->fmt.is_x_upper);
	}
	a[i++] = get_base_symbol(tmp.unb, data->fmt.is_x_upper);
	while (i > 0)
		data->fmt.num[data->fmt.num_len++] = a[--i];
}

/*unsignedotion (HEX)
*	we build a universal function for all cases (itoa_base)
*/
void	render_num(t_data *data)
{
	char	specifier;
	t_num	values;

	specifier = data->fmt.specifier;
	values.nb = 0;
	if (is_in(specifier, "di"))
	{
		values.nb = (long long)va_arg(data->ap, int);
		data->fmt.is_signed_value = true;
		if (values.nb < 0)
			data->fmt.is_negative = true;
	}
	else if (is_in(specifier, "p"))
		values.unb = (unsigned long long)va_arg(data->ap, void *);
	else if (is_in(specifier, "xXu"))
	{
		values.unb = (unsigned long long)va_arg(data->ap, unsigned int);
		if (specifier == 'X')
			data->fmt.is_x_upper = true;
	}
	print_num(data, values);
}
