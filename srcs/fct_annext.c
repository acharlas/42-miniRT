/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_annext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:19:13 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 15:40:52 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float maxf(float a, float b)
{
	if (a >= b)
		return (a);
	return(b);
}

float ft_fabs(float a)
{
	if(a < 0)
		return(-a);
	return(a);
}

float minf(float a, float b)
{
	if (a >= b)
		return (b);
	return(a);
}


unsigned int	color_to_int(__m128 v)
{
	float tmp[4];
	_mm_storeu_ps(tmp, v);
	unsigned int color;
	if (tmp[0] > 1)
		tmp[0] = 1;
	if (tmp[1] > 1)
		tmp[1] = 1;
	if (tmp[2] > 1)
		tmp[2] = 1;
	color = (int)(255 * tmp[0]) << 16;
	color |= (int)(255 * tmp[1]) << 8;
	color |= (int)(255 * tmp[2]);
	return (color);
}
