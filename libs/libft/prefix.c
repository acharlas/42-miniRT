/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:07:06 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:07:07 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_prefixes(t_conv *out)
{
	if (out->conv_symbol == 's')
		return ;
	if (!*out->prefixes && *out->value == '-' \
			&& out->flags & (PRECISION | ZERO))
		out->prefixes[0] = '-';
	if (!*out->prefixes && out->flags & ADD_SIGN && *out->value != '-')
		out->prefixes[0] = '+';
	if (!*out->prefixes && out->flags & SPACE && *out->value != '-' \
			&& ft_strchr("di", out->conv_symbol))
		out->prefixes[0] = ' ';
	if (out->flags & ALTERNATE && ft_strchr("xXp", out->conv_symbol))
	{
		if (*out->value == '0' && out->conv_symbol != 'p')
			return ;
		out->prefixes[1] = '0';
		if (!*out->value)
			return ;
		if (out->conv_symbol == 'x' || out->conv_symbol == 'p')
			out->prefixes[2] = 'x';
		else if (out->conv_symbol == 'X')
			out->prefixes[2] = 'X';
	}
}

void	add_prefixes(t_conv *out)
{
	char *tmp;
	char *tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (out->prefixes[0] && out->prefixes[0] != '-')
	{
		if (!(tmp = ft_calloc(sizeof(char), 2)))
			return ;
		ft_memcpy(tmp, out->prefixes, 1);
		tmp2 = out->value;
		out->value = ft_strjoin(tmp, tmp2);
		out->len += 1;
	}
	if (out->prefixes[2])
	{
		if (!(tmp = ft_calloc(sizeof(char), 3)))
			return ;
		ft_memcpy(tmp, out->prefixes + 1, 2);
		tmp2 = out->value;
		out->value = ft_strjoin(tmp, tmp2);
		out->len += 2;
	}
	free(tmp);
	free(tmp2);
}
