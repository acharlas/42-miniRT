/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:04:27 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:04:29 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pad(t_conv *out, int howmany, char with, char dir)
{
	char	*tmp;
	char	*fill;

	if (*out->value == '-' && out->value[1] != '0' \
			&& (out->flags & PRECISION || with == '0'))
		howmany++;
	if (howmany > 0)
	{
		tmp = out->value;
		if (!(fill = ft_calloc(sizeof(char), howmany + 1)))
			return ;
		ft_memset(fill, with, howmany);
		if (dir == 1)
			out->value = ft_special_join(out->value, fill, out->len, howmany);
		else if (dir == -1 && with == '0')
			out->value = carry_and_join(fill, out->value);
		else if (dir == -1)
			out->value = ft_special_join(fill, out->value, howmany, out->len);
		free(tmp);
		free(fill);
		out->len += howmany;
	}
}

int		cnt_dig(int n)
{
	int		i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_strupcase(char *str)
{
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}

char	*carry_and_join(char *s1, char *s2)
{
	char	*tmp;
	char	*out;
	char	*sub;
	char	*pos;

	if ((pos = ft_strnstr(s2, "0x", 2))  \
			|| (pos = ft_strnstr(s2, "-", 2)) \
			|| (pos = ft_strnstr(s2, "+", 2)) \
			|| (pos = ft_strnstr(s2, " ", 2)) \
			|| (pos = ft_strnstr(s2, "0X", 2)))
	{
		sub = ft_substr(s2, pos - s2, pos - s2 + (*pos == '0' ? 2 : 1));
		out = ft_strjoin(s1, s2 + (*pos == '0' ? 2 : 1));
		tmp = out;
		out = ft_strjoin(sub, out);
		free(tmp);
		free(sub);
	}
	else
		out = ft_strjoin(s1, s2);
	return (out);
}

char	*ft_special_join(char *s1, char *s2, int len1, int len2)
{
	char	*out;

	if (!(out = malloc(sizeof(char) * len1 + len2)))
		return (NULL);
	ft_memcpy(out, s1, len1);
	ft_memcpy(out + len1, s2, len2);
	return (out);
}
