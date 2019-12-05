/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdeban <rdeban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:29:26 by rdeban            #+#    #+#             */
/*   Updated: 2019/11/20 16:25:09 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_strlen(const char *s)
{
	const char *i = s;

	while (*i)
		i++;
	return (i - s);
}

void			*ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t	big_dst;
	size_t	delim;

	if (!(size && (dst || src)))
		return (dst);
	big_dst = (size_t)dst;
	while ((big_dst % sizeof(size_t)) != 0 && size)
	{
		*(unsigned char *)big_dst++ = *(unsigned char *)src++;
		size--;
	}
	delim = size / sizeof(size_t);
	while (delim-- > 0)
	{
		*(size_t *)big_dst = *(size_t *)src;
		big_dst += sizeof(size_t);
		src += sizeof(size_t);
	}
	size %= sizeof(size_t);
	while (size-- > 0)
		*(unsigned char *)big_dst++ = *(unsigned char *)src++;
	return (dst);
}

char			*join(char *s1, char *s2, int len1, int len2)
{
	char *out;

	out = malloc(sizeof(char) * (len1 + len2 + 1));
	ft_memcpy(out, s1, len1);
	ft_memcpy(out + len1, s2, len2);
	out[len1 + len2] = '\0';
	free(s1);
	return (out);
}

char			*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!len || !s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (!(dst = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memcpy(dst, s + start, len);
	dst[len] = '\0';
	return (dst);
}

void			*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ps;

	ps = (unsigned char *)s;
	while (n--)
		if (*ps++ == (unsigned char)c)
			return ((void *)ps - 1);
	return (NULL);
}
