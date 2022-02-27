/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_atof.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:35 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:36 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_simple_atof(const char *str)
{
	float	out;
	char	neg;
	int		digbeforedot;

	out = 0;
	digbeforedot = 0;
	neg = 1;
	while (*str && (*str == '-' || *str == '+'))
	{
		if (*(str++) == '-')
			neg = -neg;
	}
	while (str[digbeforedot] && str[digbeforedot] != '.')
		digbeforedot++;
	while (*str)
	{
		if (*str && ft_isdigit(*str))
			out += (*str - '0') * pow(10, --digbeforedot);
		str++;
	}
	return (out * neg);
}
