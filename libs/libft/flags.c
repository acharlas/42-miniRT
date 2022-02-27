/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:50:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:00:57 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_setter(char c, t_conv *out)
{
	if (c == '#')
		out->flags |= ALTERNATE;
	else if (c == '-')
	{
		out->flags |= LEFT_ALIGN;
		if (out->flags & ZERO)
			out->flags &= ~ZERO;
	}
	else if (c == '+')
	{
		out->flags |= ADD_SIGN;
		if (out->flags & SPACE)
			out->flags &= ~SPACE;
	}
	else if (c == '.')
	{
		out->flags |= PRECISION;
		if (out->flags & ZERO)
			out->flags &= ~ZERO;
	}
	else if (c == ' ' && !(out->flags & ADD_SIGN))
		out->flags |= SPACE;
	else if (c == '0' && !(out->flags & (LEFT_ALIGN | PRECISION)))
		out->flags |= ZERO;
}

void		set_flags(const char **format, t_conv *out)
{
	while (ft_strchr("#0- +'", **format))
	{
		flag_setter(**format, out);
		(*format)++;
	}
}
