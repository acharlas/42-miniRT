/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:01:32 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:01:34 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *dst;

	if (!count || !size)
	{
		size = 1;
		count = 1;
	}
	if (!(dst = malloc(size * count)))
		return (NULL);
	ft_bzero(dst, size * count);
	return (dst);
}
