/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:06:24 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:06:25 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!len || !s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (!(dst = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	(void)ft_strlcpy(dst, s + start, len + 1);
	return (dst);
}
