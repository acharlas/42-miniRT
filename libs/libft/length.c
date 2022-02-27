/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:06:45 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:06:45 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	length_mod_setter(char c, t_conv *out)
{
	if (c == 'l' && out->flags & LONG)
	{
		out->flags |= LONG_LONG;
		out->flags ^= LONG;
	}
	else if (c == 'l')
		out->flags |= LONG;
	else if (c == 'h' && out->flags & SHORT)
	{
		out->flags |= CHAR;
		out->flags ^= SHORT;
	}
	else if (c == 'h')
		out->flags |= SHORT;
}

void		set_length_mod(const char **format, t_conv *out)
{
	while (**format && ft_strchr("hl", **format))
	{
		length_mod_setter(**format, out);
		(*format)++;
	}
}
