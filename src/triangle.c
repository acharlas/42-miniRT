/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:53 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:54 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ray_intersect_triangle(t_ray ray, t_triangle tr)
{
	simd_float3	h;
	float		au[2];
	float		v;
	float		t;
	simd_float3	q;

	h = simd_cross(ray.dir, tr.b - tr.a);
	if ((au[0] = simd_dot(h, tr.c - tr.a)) > -0.0001 && au[0] < 0.0001)
		return (FLT_MAX);
	au[1] = 1.f / au[0] * simd_dot(ray.orig - tr.a, h);
	if (au[1] < 0.0 || au[1] > 1.0)
		return (FLT_MAX);
	q = simd_cross(ray.orig - tr.a, tr.c - tr.a);
	v = 1.f / au[0] * simd_dot(ray.dir, q);
	if (v < 0.0 || au[1] + v > 1.0)
		return (FLT_MAX);
	t = 1.f / au[0] * simd_dot(tr.b - tr.a, q);
	if (t > 0.0001)
		return (t);
	return (FLT_MAX);
}

t_obj	*make_triangle(simd_float3 p1, simd_float3 p2, simd_float3 p3, \
	simd_float3 color)
{
	t_triangle	*t;
	t_obj		*t_o;

	t = p_malloc(sizeof(t_triangle), 1, "triangle");
	t_o = p_malloc(sizeof(t_obj), 0, "triangle");
	t->a = p1;
	t->b = p2;
	t->c = p3;
	t_o->id = TRIANGLE;
	t_o->type.triangle = t;
	t_o->color = color;
	return (t_o);
}

void	add_triangle(char **info, t_scene *scene)
{
	t_obj		*t;
	simd_float3	p1;
	simd_float3	p2;
	simd_float3	p3;
	simd_float3	color;

	if (ft_stralen(info) != 5)
		error_handling(BAD_NB_PARAM, "triangle", "");
	p1 = make_coord(info[1], "triangle");
	p2 = make_coord(info[2], "triangle");
	p3 = make_coord(info[3], "triangle");
	color = make_color(info[4], "triangle");
	t = make_triangle(p1, p2, p3, color);
	ft_lstadd_front(&scene->listobj, ft_lstnew(t));
}
