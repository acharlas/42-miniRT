/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:04:03 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:04:04 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*bs1 = (unsigned char *)s1;
	const unsigned char	*bs2 = (unsigned char *)s2;

	while ((s1 != s2) && n--)
		if (*bs1++ != *bs2++)
			return (*(bs1 - 1) - *(bs2 - 1));
	return (0);
}
