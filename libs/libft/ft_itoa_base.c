/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:02:40 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:02:46 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	dig_cnt(long c, int base)
{
	int	i;

	i = 0;
	while (c)
	{
		c /= base;
		i++;
	}
	return (i);
}

static char	*set_base_string(int n_base)
{
	char	*base;

	if (n_base == 10)
		base = ft_strdup("0123456789");
	else if (n_base == 16)
		base = ft_strdup("0123456789ABCDEF");
	else if (n_base == 8)
		base = ft_strdup("01234567");
	else if (n_base == 2)
		base = ft_strdup("01");
	else
		base = NULL;
	return (base);
}

char		*ft_itoa_base(long long c, int n_base)
{
	int			i;
	int			neg;
	char		*out;
	const char	*base = set_base_string(n_base);

	if (c == 0)
		return (ft_strdup("0"));
	i = dig_cnt(c, n_base) + (c < 0 ? 1 : 0);
	neg = (c < 0) ? -1 : 1;
	c = c * neg;
	if (!(out = malloc(sizeof(char) * i + 1)))
		return (NULL);
	out[i--] = '\0';
	while (c)
	{
		out[i--] = base[c % n_base];
		c /= n_base;
	}
	if (neg < 0)
		out[i--] = '-';
	i++;
	free((char *)base);
	return (out + i);
}
