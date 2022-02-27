/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:04:43 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:04:44 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include "libft.h"
# include <stdarg.h>
# define ADD_SIGN 0x1
# define LEFT_ALIGN 0x2
# define PRECISION 0x4
# define ALTERNATE 0x8
# define SHORT 0x10
# define LONG 0x20
# define LONG_LONG 0x40
# define SPACE 0x80
# define ZERO 0x100
# define CHAR 0x200

/*
**		Flag table
**		| hh | 0 | sp | ll | l | h | # | pre | - | + |
*/

typedef struct	s_conv
{
	char	*value;
	int		f_width;
	long	flags;
	int		precision;
	char	conv_symbol;
	int		len;
	char	prefixes[3];
}				t_conv;

int				ft_printf(const char *format, ...);
int				ft_fdprintf(int fd, const char *format, ...);
int				ft_asprintf(char **strp, const char *format, ...);
t_conv			*struct_builder(int f_len, va_list ap, const char **s);
t_conv			*struct_init(void);
char			*ft_itoa_base(long long n, int n_base);
int				ft_printf(const char *format, ...);
void			set_arg(va_list ap, t_conv *toprint);
void			set_flags(const char **format, t_conv *out);
void			set_length_mod(const char **format, t_conv *out);
void			set_field(va_list ap, const char **format, t_conv *out);
void			set_precision(va_list ap, const char **format, t_conv *out);
void			set_prefixes(t_conv *out);
void			add_prefixes(t_conv *out);
int				cnt_dig(int n);
void			ft_strupcase(char *str);
char			*carry_and_join(char *s1, char *s2);
char			*ft_special_join(char *s1, char *s2, int len1, int len2);
char			*j_and_free_and_len(char *s1, char *s2, int *len1, int len2);
int				write_and_free(int fd, char *s, int len);
void			free_struct(t_conv *toprint);
void			ft_pad(t_conv *out, int howmany, char with, char dir);
void			arg_setter_di(va_list ap, t_conv *toprint);
void			arg_setter_u(va_list ap, t_conv *toprint);
void			arg_setter_o(va_list ap, t_conv *toprint);
void			arg_setter_x(va_list ap, t_conv *toprint);
void			arg_setter_s(va_list ap, t_conv *toprint);
void			arg_setter_c(va_list ap, t_conv *toprint);
void			arg_setter_n(int f_len, va_list ap, t_conv *toprint);

#endif
