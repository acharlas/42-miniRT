/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:50:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:00:52 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	arg_setter_s(va_list ap, t_conv *toprint)
{
	size_t			len;
	const size_t	prec = toprint->precision;
	char			*tmp;

	tmp = va_arg(ap, char *);
	if (tmp)
	{
		len = ft_strlen(tmp);
		toprint->value = ft_strndup(tmp, toprint->flags \
				& PRECISION ? prec : len);
	}
	else
		toprint->value = ft_strndup("(null)", toprint->flags \
				& PRECISION ? prec : 6);
}

void	arg_setter_c(va_list ap, t_conv *toprint)
{
	char c;

	c = va_arg(ap, int);
	toprint->value = ft_strndup(&c, 1);
	toprint->len = 1;
}

void	arg_setter_n(int f_len, va_list ap, t_conv *toprint)
{
	if (toprint->flags & LONG)
		*(va_arg(ap, long *)) = (long)f_len;
	else if (toprint->flags & LONG_LONG)
		*(va_arg(ap, long *)) = (long long)f_len;
	else if (toprint->flags & SHORT)
		*(va_arg(ap, short *)) = (short)f_len;
	else if (toprint->flags & CHAR)
		*(va_arg(ap, char *)) = (char)f_len;
	else
		*(va_arg(ap, int *)) = (int)f_len;
}
