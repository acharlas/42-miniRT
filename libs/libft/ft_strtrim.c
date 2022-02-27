/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:06:20 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:06:20 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char const	*trim_left(char const *s1, char const *set)
{
	const char *s1b;

	s1b = s1;
	while (ft_strchr(set, *s1b) && *s1b)
		s1b++;
	if (*s1b == '\0')
		return (s1);
	return (s1b);
}

static char const	*trim_right(char const *s1, char const *set)
{
	const char *s1b;

	s1b = s1 + ft_strlen(s1) - 1;
	while (ft_strchr(set, *s1b) && s1b != s1)
		s1b--;
	return (s1b);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	char		*out;
	const char	*left;
	const char	*right;

	if (!set || !s1)
		return (NULL);
	if (*set == '\0' || *s1 == '\0')
		return (ft_strdup(s1));
	left = trim_left(s1, set);
	right = trim_right(s1, set);
	if (right - left == 0)
		return (ft_strdup(""));
	if (!(out = malloc(sizeof(char) * (right - left) + 2)))
		return (NULL);
	ft_memcpy(out, left, right - left + 1);
	out[right - left + 1] = '\0';
	return (out);
}
