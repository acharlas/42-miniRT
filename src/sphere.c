/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:47 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:48 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ray_intersect_sphere(t_ray ray, const t_sphere sp)
{
	simd_float3	l;
	float		tca;
	float		d2;
	float		thc;
	float		t0;

	l = sp.orig - ray.orig;
	tca = simd_dot(l, ray.dir);
	if (tca < 0)
		return (FLT_MAX);
	d2 = simd_dot(l, l) - (tca * tca);
	if (d2 > powf(sp.diameter / 2.f, 2))
		return (FLT_MAX);
	thc = sqrtf(powf(sp.diameter / 2.f, 2) - d2);
	t0 = tca - thc;
	if (t0 < 0)
		t0 = tca + thc;
	if (t0 < 0)
		return (FLT_MAX);
	return (t0);
}

t_obj	*make_sphere(simd_float3 orig, float diam, simd_float3 color)
{
	t_sphere	*s;
	t_obj		*s_o;

	s = p_malloc(sizeof(t_sphere), 1, "sphere");
	s_o = p_malloc(sizeof(t_obj), 0, "sphere");
	s->orig = orig;
	s->diameter = diam;
	s_o->id = SPHERE;
	s_o->type.sphere = s;
	s_o->color = color;
	return (s_o);
}

void	add_sphere(char **info, t_scene *scene)
{
	t_obj		*sphere;
	simd_float3	orig;
	simd_float3	color;
	float		diam;

	if (ft_stralen(info) != 4)
		error_handling(BAD_NB_PARAM, "sphere", "");
	orig = make_coord(info[1], "sphere");
	color = make_color(info[3], "sphere");
	if (!ft_is_floatstr(info[2]))
		error_handling(INVALID_VALUE, "sphere", " diameter");
	diam = ft_simple_atof(info[2]);
	if (diam <= 0)
		error_handling(OUT_OF_RANGE, "sphere", " diameter");
	sphere = make_sphere(orig, diam, color);
	ft_lstadd_front(&scene->listobj, ft_lstnew(sphere));
}
