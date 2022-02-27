/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:02:51 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:02:52 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dec_cnt(int c)
{
	int	i;

	i = 0;
	while (c)
	{
		c /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int c)
{
	int		i;
	int		neg;
	char	*out;

	if (c == 0)
		return (ft_strdup("0"));
	if (c == -2147483648)
		return (ft_strdup("-2147483648"));
	i = dec_cnt(c) + (c < 0 ? 1 : 0);
	neg = 1;
	if (c < 0)
		neg *= -1;
	c = c * neg;
	if (!(out = malloc(sizeof(char) * i + 1)))
		return (NULL);
	out[i--] = '\0';
	while (c)
	{
		out[i--] = c % 10 + 48;
		c /= 10;
	}
	if (neg < 0)
		out[i--] = '-';
	i++;
	return (out + i);
}
