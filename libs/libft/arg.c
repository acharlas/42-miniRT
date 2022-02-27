/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:50:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:00:46 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_arg(va_list ap, t_conv *toprint)
{
	if (ft_strchr("di", toprint->conv_symbol))
		arg_setter_di(ap, toprint);
	else if (toprint->conv_symbol == 'u')
		arg_setter_u(ap, toprint);
	else if (toprint->conv_symbol == 'o')
		arg_setter_o(ap, toprint);
	else if (ft_strchr("xX", toprint->conv_symbol))
		arg_setter_x(ap, toprint);
	else if (toprint->conv_symbol == 's')
		arg_setter_s(ap, toprint);
	else if (toprint->conv_symbol == 'c')
		arg_setter_c(ap, toprint);
	else if (toprint->conv_symbol == '%')
		toprint->value = ft_strdup("%");
	else if (ft_strchr("p", toprint->conv_symbol))
	{
		toprint->value = ft_itoa_base(va_arg(ap, long), 16);
		ft_strupcase(toprint->value);
		toprint->flags |= ALTERNATE;
	}
	else
		return ;
	if (toprint->conv_symbol != 'c')
		toprint->len = ft_strlen(toprint->value);
}

void	arg_setter_di(va_list ap, t_conv *toprint)
{
	if (toprint->flags & LONG)
		toprint->value = ft_itoa_base(va_arg(ap, long), 10);
	else if (toprint->flags & LONG_LONG)
		toprint->value = ft_itoa_base(va_arg(ap, long long), 10);
	else if (toprint->flags & SHORT)
		toprint->value = ft_itoa_base((short)va_arg(ap, long), 10);
	else if (toprint->flags & CHAR)
		toprint->value = ft_itoa_base((char)va_arg(ap, long), 10);
	else
		toprint->value = ft_itoa_base(va_arg(ap, int), 10);
}

void	arg_setter_u(va_list ap, t_conv *toprint)
{
	if (toprint->flags & LONG)
		toprint->value = ft_itoa_base(va_arg(ap, unsigned long), 10);
	else if (toprint->flags & LONG_LONG)
		toprint->value = ft_itoa_base(va_arg(ap, unsigned long long), 10);
	else if (toprint->flags & SHORT)
		toprint->value = \
			ft_itoa_base((unsigned short)va_arg(ap, unsigned int), 10);
	else if (toprint->flags & CHAR)
		toprint->value = \
			ft_itoa_base((unsigned char)va_arg(ap, unsigned int), 10);
	else
		toprint->value = ft_itoa_base(va_arg(ap, unsigned int), 10);
}

void	arg_setter_o(va_list ap, t_conv *toprint)
{
	if (toprint->flags & LONG)
		toprint->value = ft_itoa_base(va_arg(ap, unsigned long), 8);
	else if (toprint->flags & LONG_LONG)
		toprint->value = ft_itoa_base(va_arg(ap, unsigned long long), 8);
	else if (toprint->flags & SHORT)
		toprint->value = \
			ft_itoa_base((unsigned short)va_arg(ap, unsigned int), 8);
	else if (toprint->flags & CHAR)
		toprint->value = \
			ft_itoa_base((unsigned char)va_arg(ap, unsigned int), 8);
	else
		toprint->value = ft_itoa_base(va_arg(ap, unsigned int), 8);
}

void	arg_setter_x(va_list ap, t_conv *toprint)
{
	if (toprint->flags & LONG)
		toprint->value = ft_itoa_base(va_arg(ap, unsigned long), 16);
	else if (toprint->flags & LONG_LONG)
		toprint->value = ft_itoa_base(va_arg(ap, unsigned long long), 16);
	else if (toprint->flags & SHORT)
		toprint->value = \
			ft_itoa_base((unsigned short)va_arg(ap, unsigned int), 16);
	else if (toprint->flags & CHAR)
		toprint->value = \
			ft_itoa_base((unsigned char)va_arg(ap, unsigned int), 16);
	else
		toprint->value = ft_itoa_base(va_arg(ap, unsigned int), 16);
	if (toprint->conv_symbol == 'x')
		ft_strupcase(toprint->value);
}
