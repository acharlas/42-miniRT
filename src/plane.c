/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:03 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:04 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ray_intersect_plane(t_ray ray, const t_plane pl)
{
	float		denom;
	float		t;
	simd_float3	dif;

	denom = simd_dot(pl.orient, ray.dir);
	if (ft_fabs(denom) > 0.0001)
	{
		dif = pl.orig - ray.orig;
		t = simd_dot(dif, pl.orient) / denom;
		if (t > 0.0001)
			return (t);
	}
	return (FLT_MAX);
}

t_obj	*make_plane(simd_float3 orig, simd_float3 orient, simd_float3 color)
{
	t_plane *p;
	t_obj	*p_o;

	p = p_malloc(sizeof(t_plane), 1, "plane");
	p_o = p_malloc(sizeof(t_obj), 0, "plane");
	p->orig = orig;
	p->orient = orient;
	p_o->id = PLANE;
	p_o->type.plane = p;
	p_o->color = color;
	return (p_o);
}

void	add_plane(char **info, t_scene *scene)
{
	t_obj		*p;
	simd_float3	orig;
	simd_float3	orient;
	simd_float3	color;

	if (ft_stralen(info) != 4)
		error_handling(BAD_NB_PARAM, "plane", "");
	orig = make_coord(info[1], "plane");
	orient = make_orient(info[2], "plane");
	color = make_color(info[3], "plane");
	p = make_plane(orig, orient, color);
	ft_lstadd_front(&scene->listobj, ft_lstnew(p));
}
