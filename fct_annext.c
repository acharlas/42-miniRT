/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_annext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:19:13 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/26 17:01:48 by acharlas         ###   ########.fr       */
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


int	c_color(vect3f a)
{
	int color;
	color = (int)(255 * a.x) << 16;
	color |= (int)(255 * a.y) << 8;
	color |= (int)(255 * a.z);
	return (color);
}

vect3f	bg_color(float a, float b, float c)
{
	return (c_vect3f(a/255, b/255, c/255));
}

vect3f	verif_color(vect3f color)
{
	if (color.x > 1)
		color.x = 1;
	if (color.y > 1)
		color.y = 1;
	if (color.z > 1)
		color.z = 1;
	if (color.x < 0)
		color.x = 0.001;
	if (color.y < 0)
		color.y = 0.001;
	if (color.z < 0)
		color.z = 0.001;
	return (color);
}