/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:10:46 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/28 16:58:57 by raphael          ###   ########.fr       */
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
	return (v_div(this, norm(this)));
}

float v_dot(vect3f a, vect3f b)
{
	return(a.x * b.x + a.y * b.y + a.z * b.z);
}

vect3f	v_mult(vect3f a, float b)
{
	return (c_vect3f(a.x * b, a.y * b, a.z * b));
}

vect3f	v_plus(vect3f a, vect3f b)
{
	return (c_vect3f(a.x + b.x, a.y + b.y, a.z + b.z));
}

vect3f v_minus(vect3f a, vect3f b)
{
	return (c_vect3f(a.x - b.x, a.y - b.y, a.z - b.z));
}

vect3f v_multv(vect3f a, vect3f b)
{
	return (c_vect3f(a.x * b.x, a.y * b.y, a.z * b.z));
}

vect3f	v_div(vect3f a, float b)
{
	return(c_vect3f(a.x / b, a.y / b, a.z / b));
}

vect3f	v_divv(vect3f a, vect3f b)
{
	return(c_vect3f(a.x / b.x, a.y / b.y, a.z / b.z));
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

bool		ray_intersect_square(const vect3f *orig, const vect3f *dir, float *t0, const t_square square)
{
	if (ft_fabs(dir->y) > 0.001)
	{
		float d = -(orig->y - square.pos.y)/ dir->y; 
		vect3f pt = v_plus(*orig,v_mult(*dir,d));
		if(d > 0 && ft_fabs(pt.x)<10 && pt.z<-10 && pt.z>-30)
		{
			*t0 = d;
			return(1);
		}
		return (0);
	}
	return (0);
}
