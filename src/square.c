/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:13:44 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:13:46 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ray_intersect_square(t_ray ray, t_square sq)
{
	simd_float3	k;
	simd_float3	t1;
	simd_float3	t2;
	float		tn;
	float		tf;

	ray.orig = ray.orig - sq.orig;
	ray.orig = simd_mul(ray.orig, align_with(sq.orient));
	ray.dir = simd_mul(ray.dir, align_with(sq.orient));
	k = simd_abs(1.f / ray.dir) * simd_make_float3(sq.height / 2.f,
			sq.height / 2.f, 0);
	t1 = -(1.f / ray.dir) * ray.orig - k;
	t2 = -(1.f / ray.dir) * ray.orig + k;
	tn = MAX(MAX(t1.x, t1.y), t1.z);
	tf = MIN(MIN(t2.x, t2.y), t2.z);
	if (tn > tf || tf < 0.f)
		return (FLT_MAX);
	return (tf);
}

t_obj	*make_square(simd_float3 orig, simd_float3 orient, float height, \
	simd_float3 color)
{
	t_square	*sq;
	t_obj		*sq_o;

	sq = p_malloc(sizeof(t_square), 1, "square");
	sq_o = p_malloc(sizeof(t_obj), 0, "square");
	sq->orig = orig;
	sq->orient = orient;
	sq->height = height;
	sq_o->id = SQUARE;
	sq_o->type.square = sq;
	sq_o->color = color;
	return (sq_o);
}

void	add_square(char **info, t_scene *scene)
{
	t_obj		*sq;
	simd_float3	orig;
	simd_float3	orient;
	simd_float3	color;
	float		height;

	if (ft_stralen(info) != 5)
		error_handling(BAD_NB_PARAM, "square", "");
	orig = make_coord(info[1], "square");
	orient = make_orient(info[2], "square");
	if (!ft_is_floatstr(info[3]))
		error_handling(INVALID_VALUE, "square", " height");
	height = ft_simple_atof(info[3]);
	if (height <= 0)
		error_handling(OUT_OF_RANGE, "square", " height");
	color = make_color(info[4], "square");
	sq = make_square(orig, orient, height, color);
	ft_lstadd_front(&scene->listobj, ft_lstnew(sq));
}
