/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:15:15 by ntaleb            #+#    #+#             */
/*   Updated: 2022/10/31 14:43:07 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>

struct s_flags
{
	int		hash;
	int		minus;
	int		zero;
	int		plus;
	int		space;

	int		width;

	int		dot;
	int		precision;

	char	conversion;
};

void	set_flag(struct s_flags *f, char flag);
int		print_flags(struct s_flags *flags);
int		isflag(char c);
int		ft_print_padded_str(char *str, struct s_flags *flags, int _free);
int		ft_print_padded_mem(char *src, int len, struct s_flags *flags,
			int _free);
void	handle_flags(const char **fmt, struct s_flags *flags);
char	*ft_adjust_precision(char *number, int new_precision,
			struct s_flags *flags);
int		is_conversion(char c);
int		invoke_conversion(char c, va_list ap, struct s_flags *flags);
int		handle_format(const char **fmt, va_list ap, struct s_flags *flags);
int		check_precision(unsigned int i, int precision, char **s);

int		ft_print_percent(struct s_flags *flags);
int		ft_print_char(char c, struct s_flags *flags);
int		ft_print_str(char *str, struct s_flags *flags);
int		ft_print_int(int i, struct s_flags *flags);
int		ft_print_uint(unsigned int i, struct s_flags *flags);
int		ft_print_uint_hex(unsigned int i, int upper, struct s_flags *flags);
int		ft_print_ptr(void *p, struct s_flags *flags);

#endif