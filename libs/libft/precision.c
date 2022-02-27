/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:07:02 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:07:02 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_precision(va_list ap, const char **format, t_conv *out)
{
	if (**format == '.')
	{
		out->flags |= PRECISION;
		if (out->flags & ZERO)
			out->flags &= ~ZERO;
		(*format)++;
	}
	else
		return ;
	if (**format == '*')
	{
		out->precision = va_arg(ap, int);
		(*format)++;
	}
	while (ft_isdigit(**format))
		out->precision = 10 * out->precision + (*(*format)++ - 48);
}
