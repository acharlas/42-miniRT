/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:10:46 by acharlas          #+#    #+#             */
/*   Updated: 2019/12/03 18:41:49 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

vect2f	c_vect2f(float a, float b)
{
	vect2f	out;
	
	out.a = a;
	out.b = b;
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

bool	ray_intersect_sphere(const vect3f *orig, const vect3f *dir, float *t0, const t_sphere sphere)
{
	vect3f	l;
	float	tca;
	float	d2;
	float	thc;
	float	t1;

	l = v_minus(sphere.pos, *orig);
	tca = v_dot(l, *dir);
	if (tca < 0)
		return (0);
	d2 = v_dot(l, l) - (tca * tca);
	if (d2 > powf(sphere.r, 2))
		return (0);
	thc = sqrtf(powf(sphere.r, 2) - d2);
	*t0 = tca - thc;
	t1 = tca + thc;
	if (*t0 < 0)
		*t0 = t1;
	if (*t0 < 0)
		return (0);
	return (1);
}

bool	ray_intersect_square(const vect3f *orig, const vect3f *dir, float *t0, const t_square square)
{	
	vect3f n = normalize(square.rot);
	float denom = v_dot(*dir, n);
	if (ft_fabs(denom) > 0.001)
	{
		vect3f polo = v_minus(*orig, square.pos);
		*t0 = v_dot(polo, n) / denom;
		vect3f pt = v_plus(*orig,v_mult(*dir,*t0));
		if	(*t0 >= 0)
			return (1);
	}
	return (0);
}

bool	ray_intersect_cylinder(const vect3f *orig, const vect3f *dir, float *t0, const t_cylinder cylinder)
{
	vect3f v = normalize(cylinder.rot);
	vect3f x = v_minus(*orig, cylinder.pos);
	float a = v_dot(*dir, *dir) - powf(v_dot(*dir, v), 2);
	float b = 2 * (v_dot(*dir, x) - (v_dot(*dir,v) * v_dot(x,v)));
	float c = v_dot(x,x) - powf(v_dot(x,v), 2) - powf(cylinder.r, 2);

	float delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	float x1 = (-b + sqrtf(delta)) / (a * 2);
	float x2 = (-b - sqrtf(delta)) / (a * 2);
	if (x1 < x2 && x1 > 0)
	{
		*t0 = x1;
		return (1);
	}
	else if (x2 < x1 && x2 > 0)
	{
		*t0 = x2;
		return (1);
	}
	return (0);
}

bool	ray_intersect_cone(const vect3f *orig, const vect3f *dir, float *t0, const t_cone cone)
