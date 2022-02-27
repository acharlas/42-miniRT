/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:50:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:00:55 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_field(va_list ap, const char **format, t_conv *out)
{
	int width;

	if (**format == '*')
	{
		width = va_arg(ap, int);
		if (width < 0)
		{
			out->flags |= LEFT_ALIGN;
			width = -width;
		}
		out->f_width = width;
		(*format)++;
	}
	else if (ft_isdigit(**format))
	{
		out->f_width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
}
