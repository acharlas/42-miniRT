/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_annext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:19:13 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/23 11:23:48 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float maxf(float a, float b)
{
	if (a >= b)
		return (a);
	return(b);
}

int	c_color(vect3f a)
{
	int color;
	color = (int)(255 * a.x) << 16;
	color |= (int)(255 * a.y) << 8;
	color |= (int)(255 * a.z);
	return (color);
}
