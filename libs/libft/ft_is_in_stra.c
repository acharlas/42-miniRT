/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_stra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:02:04 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:02:05 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_in_stra(char *str, char **stra)
{
	if (!str || !stra)
		return (0);
	while (*stra)
	{
		if (ft_strcmp(str, *(stra++)) == 0)
			return (1);
	}
	return (0);
}
