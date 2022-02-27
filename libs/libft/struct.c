/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:07:11 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:07:12 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_struct(t_conv *toprint)
{
	if (toprint->value)
		free(toprint->value);
	free(toprint);
}

t_conv	*struct_checker(t_conv *newstruct)
{
	const char	valid_conv[11] = "cspdiouxX%";
	char		*tmp;

	if (!newstruct->conv_symbol \
			|| !ft_strchr(valid_conv, newstruct->conv_symbol))
	{
		free_struct(newstruct);
		return (NULL);
	}
	if (newstruct->conv_symbol != 's' && newstruct->flags & PRECISION \
			&& !newstruct->precision && *newstruct->value == '0')
	{
		tmp = newstruct->value;
		newstruct->value = ft_strdup("");
		newstruct->len--;
		free(tmp);
	}
	if (newstruct->conv_symbol == 'o' && newstruct->flags & ALTERNATE \
			&& newstruct->precision <= newstruct->len \
			&& *newstruct->value != '0')
	{
		newstruct->precision = newstruct->len + 1;
		newstruct->flags |= PRECISION;
	}
	return (newstruct);
}

void	make_string(t_conv *out)
{
	int			fullsz;
	const int	prec = out->precision;
	const int	len = out->len;

	if (out->conv_symbol == 's')
		fullsz = len;
	else
		fullsz = prec > len ? prec : len;
	if (out->prefixes[0])
		fullsz++;
	if (out->prefixes[2])
		fullsz += 2;
	add_prefixes(out);
	if ((out->flags & (LEFT_ALIGN | ZERO)) == ZERO)
		ft_pad(out, out->f_width - fullsz, '0', -1);
	if (out->conv_symbol != 's' && out->flags & PRECISION)
		ft_pad(out, prec - len, '0', -1);
	if ((out->flags & (LEFT_ALIGN | ZERO)) == 0)
		ft_pad(out, out->f_width - fullsz, ' ', -1);
	if (out->flags & LEFT_ALIGN)
		ft_pad(out, out->f_width - fullsz, ' ', 1);
}

t_conv	*struct_builder(int f_len, va_list ap, const char **s)
{
	t_conv		*out;

	(*s)++;
	if (!(out = struct_init()))
		return (NULL);
	set_flags(s, out);
	set_field(ap, s, out);
	set_precision(ap, s, out);
	set_length_mod(s, out);
	if (**s)
		out->conv_symbol = *(*s)++;
	set_arg(ap, out);
	if (out->conv_symbol == 'n')
		arg_setter_n(f_len, ap, out);
	out = struct_checker(out);
	if (out)
	{
		out = struct_checker(out);
		set_prefixes(out);
		make_string(out);
	}
	return (out);
}

t_conv	*struct_init(void)
{
	t_conv		*out;
	int			i;

	i = 0;
	if (!(out = malloc(sizeof(t_conv) * 1)))
		return (NULL);
	out->precision = 0;
	out->len = 0;
	out->value = NULL;
	out->f_width = 0;
	out->flags = 0;
	while (i < 3)
		out->prefixes[i++] = 0;
	return (out);
}
