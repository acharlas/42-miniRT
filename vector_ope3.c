/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:37:02 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 20:37:20 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vect3f	v_div(vect3f a, float b)
{
	vect3f out;

	out.x = a.x / b;
	out.y = a.y / b;
	out.z = a.z / b;
	return (out);
}

vect3f	v_divv(vect3f a, vect3f b)
{
	vect3f out;

	out.x = a.x / b.x;
	out.y = a.y / b.y;
	out.z = a.z / b.z;
	return (out);
}

vect3f	v_cross(vect3f a, vect3f b)
{
	vect3f c;

	c.x = a.y*b.z - a.z*b.y; 
	c.y = a.z*b.x - a.x*b.z; 
	c.z = a.x*b.y - a.y*b.x;
	return (c);
}
