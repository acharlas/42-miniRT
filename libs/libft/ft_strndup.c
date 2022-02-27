/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:06:05 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:06:06 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*out;
	int		i;

	i = 0;
	if (!(out = ft_calloc(sizeof(char), n + 1)))
		return (NULL);
	while (*s1 && n--)
	{
		out[i] = s1[i];
		i++;
	}
	return (out);
}
