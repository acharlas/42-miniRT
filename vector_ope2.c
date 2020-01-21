/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:35:50 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 20:36:24 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float v_dot(vect3f a, vect3f b)
{
	return(a.x * b.x + a.y * b.y + a.z * b.z);
}

vect3f	v_mult(vect3f a, float b)
{
	vect3f	c;

	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
	return (c);
}

vect3f	v_plus(vect3f a, vect3f b)
{
	vect3f	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

vect3f v_minus(vect3f a, vect3f b)
{
	vect3f	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

vect3f v_multv(vect3f a, vect3f b)
{
	vect3f out;

	out.x = a.x * b.x;
	out.y = a.y * b.y;
	out.z = a.z * b.z;
	return (out);
}
