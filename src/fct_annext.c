/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_annext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:28 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:29 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_clamp(float a)
{
	if (a < 0)
		return (0);
	else if (a > 1)
		return (1);
	return (a);
}

float	maxf(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

float	ft_fabs(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}

float	minf(float a, float b)
{
	if (a >= b)
		return (b);
	return (a);
}
