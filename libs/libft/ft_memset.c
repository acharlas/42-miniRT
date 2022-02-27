/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:04:23 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:04:24 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bst;
	unsigned char	cst;

	cst = (unsigned char)c;
	bst = (unsigned char *)b;
	while (len--)
		*bst++ = cst;
	return (b);
}
