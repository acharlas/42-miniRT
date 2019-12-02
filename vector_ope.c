/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:10:46 by acharlas          #+#    #+#             */
/*   Updated: 2019/12/02 15:00:15 by acharlas         ###   ########.fr       */
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
	
	out.x = this.x / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.y = this.y / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.z = this.z / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
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
	float d = (v_dot(square.rot, square.pos) - v_dot(square.rot, *orig)) / v_dot(square.rot, *dir);
	vect3f pt = v_plus(square.pos,v_mult(*dir,d));
	if(d > 0.0001 && ft_fabs(pt.x) < square.taille.a && ft_fabs(pt.z) < square.taille.b)
	{
		*t0 = d;
		return(1);
	}
	return (0);
}

bool	ray_intersect_cylinder(const vect3f *orig, const vect3f *dir, float *t0, const t_cylinder cylinder)
{
	double disc;


	vect3f dist = v_minus(*orig, cylinder.pos);
	normalize(cylinder.rot);
	float a = v_dot(*dir, *dir) - pow(v_dot(*dir, cylinder.rot), 2);
	float b = 2 * (v_dot(*dir, dist) - (v_dot(*dir, cylinder.rot) * v_dot(dist, cylinder.rot)));
	float c = v_dot(dist, dist) - pow(v_dot(dist, cylinder.rot), 2) - pow(cylinder.r, 2);
	disc = b * b - 4 * a * c;
	vect3f pt = v_plus(cylinder.pos,v_mult(*dir,disc));
	if (disc < 0)
		return (0);
	*t0 = (-b + sqrtf(disc)) / (2 * a);
	float t1 = (-b - sqrtf(disc)) / (2 * a);
	if (*t0 > t1)
		*t0 = t1;
	if(ft_fabs(pt.z) > 0 && ft_fabs(pt.z) < cylinder.h)
		return (1);
	return (0);
}
