/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:04:14 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:04:15 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*srcn = (char *)src;
	char		*dstn;

	dstn = (char *)dst;
	if (!dst && !src)
		return (dst);
	if (srcn < dstn)
		while ((int)(--len) >= 0)
			*(dstn + len) = *(srcn + len);
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
