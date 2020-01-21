/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:10:46 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 20:37:25 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vect2f	c_vect2f(float a, float b)
{
	vect2f	out;
	
	out.a = a;
	out.b = b;
	return (out);
}

vect3f	c_vect3f(float a, float b, float c)
{
	vect3f	out;
	
	out.x = a;
	out.y = b;
	out.z = c;
	return (out);
}

vect4f	c_vect4f(float a, float b, float c, float d)
{
	vect4f	out;
	
	out.i = a;
	out.j = b;
	out.k = c;
	out.l = d;
	return (out);
}

float	norm(vect3f a)
{
	float out;

	out = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	return (out);
}

vect3f	normalize(vect3f this)
{
	vect3f	out;
	
	out.x = this.x / sqrtf(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.y = this.y / sqrtf(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.z = this.z / sqrtf(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	return (out);
}
