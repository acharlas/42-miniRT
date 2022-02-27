/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:05:43 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:05:44 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*d;
	const char	*s;
	size_t		u;
	size_t		dlen;

	d = dst;
	s = src;
	u = dstsize;
	while (u-- && *d)
		d++;
	dlen = d - dst;
	u = dstsize - dlen;
	if (!u)
		return (dlen + ft_strlen(s));
	while (*s)
	{
		if (u != 1)
		{
			*d++ = *s;
			u--;
		}
		s++;
	}
	*d = '\0';
	return (dlen + (s - src));
}
