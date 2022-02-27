/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:04:37 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:04:38 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	t_conv	*out;
	int		f_len;
	char	*conv;
	char	*out_s;

	f_len = 0;
	out_s = ft_strdup("");
	va_start(ap, format);
	while (*format)
	{
		conv = ft_strchr(format, '%');
		out_s = j_and_free_and_len(out_s, (char *)format, &f_len, conv ? \
				(size_t)(conv - format) : ft_strlen(format));
		format += conv ? (size_t)(conv - format) : ft_strlen(format);
		if (*format == '%')
			if ((out = struct_builder(f_len, ap, &format)))
			{
				out_s = j_and_free_and_len(out_s, out->value, &f_len, out->len);
				free_struct(out);
			}
	}
	va_end(ap);
	write_and_free(1, out_s, f_len);
	return (f_len);
}
