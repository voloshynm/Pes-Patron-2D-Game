/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:50:33 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/03/16 15:50:35 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdarg.h>

// error coding
enum e_error
{
	OK = 0,
	MALLOC_ERROR = -1,
	PARSE_ERROR = -2
};

// to store unsigned 64-bit integer we use union,
// aka Two's complement https://en.wikipedia.org/wiki/Two%27s_complement
typedef union u_num
{
	long long			nb;
	unsigned long long	unb;
}	t_num;

// ---------------- structs ----------------
// struct for argument format %[flags][width][.precision][length]specifier
typedef struct s_format
{
	bool				is_plus;
	bool				is_space;
	bool				is_hash;
	bool				is_left;
	bool				is_zero_pad;
	int					width;
	int					precision;
	char				specifier;
	unsigned long long	base;
	bool				is_x_upper;
	bool				is_negative;
	bool				is_abs;
	bool				is_signed_value;
	char				num[64];
	int					num_len;
	int					padding_zeros;
	int					padding_spaces;
}	t_format;

// struct for storing arguments
	//*s: copy of pointer to format
	//ap: va list to iterate through arguments
	//chars_written: counter for written chars for printf return
	//fmt: format of the argument
typedef struct s_data
{
	const char	*s;
	va_list		ap;
	int			chars_written;
	t_format	fmt;
}	t_data;

// ---------------- funcs ------------------
int		ft_printf(const char *format, ...);
int		parse_format(t_data *data);
int		print_format(t_data *data);
void	render_char(t_data *data, int c);
void	render_str(t_data *data, char *s);
void	render_num(t_data *data);
void	putchar_n(t_data *data, int n, int c );
void	putstr_n(t_data *data, int n, char *s );
void	print_num(t_data *data, t_num values);
void	itoa_base(t_data *data, t_num values);

// ---------------- utils ------------------
bool	is_in(char c, const char *s);
int		my_strlen(char *s);
char	*ft_strdup_pf(const char *s);
char	get_base_symbol(long int index, bool is_upper);

#endif
