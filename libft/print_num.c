/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:28:33 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/26 17:28:36 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	set_padding_zeros(t_data *data)
{
	if (data->fmt.precision >= 0)
	{
		if (data->fmt.precision > data->fmt.num_len)
			data->fmt.padding_zeros = data->fmt.precision - data->fmt.num_len;
	}
	else if (data->fmt.is_zero_pad && !data->fmt.is_left)
	{
		if (data->fmt.width > data->fmt.num_len)
			data->fmt.padding_zeros = data->fmt.width - data->fmt.num_len;
		if ((is_in(data->fmt.specifier, "xX") && data->fmt.is_hash
				&& data->fmt.num[0] != '0') || data->fmt.specifier == 'p')
			data->fmt.padding_zeros = data->fmt.padding_zeros - 2;
		else if (data->fmt.is_negative || (!data->fmt.is_negative
				&& (data->fmt.is_plus || data->fmt.is_space)))
			data->fmt.padding_zeros = data->fmt.padding_zeros - 1;
	}
	if (data->fmt.padding_zeros < 0
		|| (data->fmt.specifier == 'p' && data->fmt.num[0] == '0'))
		data->fmt.padding_zeros = 0;
}

static void	set_padding_spaces(t_data *data)
{
	data->fmt.padding_spaces = data->fmt.width - \
		data->fmt.padding_zeros - data->fmt.num_len;
	if ((is_in(data->fmt.specifier, "xX") && data->fmt.is_hash
			&& data->fmt.num[0] != '0') || data->fmt.specifier == 'p')
	{
		if (data->fmt.specifier == 'p' && data->fmt.num[0] == '0')
			data->fmt.padding_spaces = data->fmt.padding_spaces - 4;
		else
			data->fmt.padding_spaces = data->fmt.padding_spaces - 2;
	}
	if (data->fmt.is_negative || (!data->fmt.is_negative
			&& (data->fmt.is_plus || data->fmt.is_space)))
		data->fmt.padding_spaces = data->fmt.padding_spaces - 1;
	if (data->fmt.padding_spaces < 0)
		data->fmt.padding_spaces = 0;
}

static void	put_sign(t_data *data)
{
	if ((is_in(data->fmt.specifier, "xX") && data->fmt.is_hash
			&& data->fmt.num[0] != '0')
		|| (data->fmt.specifier == 'p' && !(data->fmt.num[0] == '0')))
	{
		if (data->fmt.is_x_upper)
			putstr_n(data, 2, "0X");
		else
			putstr_n(data, 2, "0x");
	}
	else if (is_in(data->fmt.specifier, "di"))
	{
		if (data->fmt.is_negative)
			putchar_n(data, 1, '-');
		else if (data->fmt.is_plus)
			putchar_n(data, 1, '+');
		else if (data->fmt.is_space)
			putchar_n(data, 1, ' ');
	}
}

static void	print_space_fix_u(t_data *data)
{
	if (is_in(data->fmt.specifier, "u") && (data->fmt.is_space
			|| data->fmt.is_plus) && data->fmt.padding_spaces > 0)
		putchar_n(data, 1, ' ');
}

/*	Testing: put after line with tmp = values;
	printf(M"\nLEFT %d\nPLUS %d\nSPACE %d\nHASH %d\n"
		"ZERO_PAD %d\nWIDTH %d\nPRECISION %d\n"
		"SPECIFIER %c\nis_negative %d\nis_abs %d\nbase %d\n"
		"padding_zeros %c\npadding_spaces %d\n"
		"num_len %d\nnum[0] %c\nnum[1] %c\nnum[2] %c\n"RST"\n",
		data->fmt.is_left,
		data->fmt.is_plus,
		data->fmt.is_space,
		data->fmt.is_hash,
		data->fmt.is_zero_pad,
		data->fmt.width,
		data->fmt.precision,
		data->fmt.specifier,
		data->fmt.is_negative,
		data->fmt.is_abs,
		data->fmt.base,
		data->fmt.padding_zeros,
		data->fmt.padding_spaces,
		data->fmt.num_len,
		data->fmt.num[0],
		data->fmt.num[1],
		data->fmt.num[2]
		);
*/
void	print_num(t_data *data, t_num values)
{
	itoa_base(data, values);
	set_padding_zeros(data);
	set_padding_spaces(data);
	if (data->fmt.is_left)
	{
		put_sign(data);
		putchar_n (data, data->fmt.padding_zeros, '0');
		if (data->fmt.specifier == 'p' && data->fmt.num[0] == '0')
			putstr_n(data, 5, "(nil)");
		else
			putstr_n (data, data->fmt.num_len, data->fmt.num);
		putchar_n(data, data->fmt.padding_spaces, ' ');
		print_space_fix_u(data);
	}
	else
	{
		putchar_n(data, data->fmt.padding_spaces, ' ');
		print_space_fix_u(data);
		put_sign(data);
		putchar_n (data, data->fmt.padding_zeros, '0');
		if (data->fmt.specifier == 'p' && data->fmt.num[0] == '0')
			putstr_n(data, 5, "(nil)");
		else
			putstr_n (data, data->fmt.num_len, data->fmt.num);
	}
}
