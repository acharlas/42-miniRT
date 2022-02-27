/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_floatstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:01:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:01:59 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_floatstr(char *str)
{
	int pointfound;

	pointfound = 0;
	while (*str)
	{
		if ((*str != '+' && *str != '-' && *str != '.') && !ft_isdigit(*str))
			return (0);
		if (*str == '.')
		{
			if (pointfound)
				return (0);
			pointfound = 1;
		}
		str++;
	}
	return (1);
}
