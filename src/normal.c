/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:57 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:58 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static simd_float3	trianglenormal(t_triangle *triangle, simd_float3 dir)
{
	const simd_float3 c1 = triangle->a - triangle->b;
	const simd_float3 c2 = triangle->a - triangle->c;
	const simd_float3 normal = simd_normalize(simd_cross(c1, c2));

	if (simd_dot(normal, dir) > 0)
		return (-normal);
	return (normal);
}

static simd_float3	planenormal(t_plane *plane, simd_float3 dir)
{
	const simd_float3 normal = plane->orient;

	if (simd_dot(normal, dir) > 0)
		return (-normal);
	return (normal);
}

static simd_float3	cylindernormal(simd_float3 normal, simd_float3 dir)
{
	if (simd_dot(normal, dir) > 0)
		return (-normal);
	return (normal);
}

static simd_float3	squarenormal(simd_float3 normal, simd_float3 dir)
{
	if (simd_dot(normal, dir) > 0)
		return (-normal);
	return (normal);
}

simd_float3			get_normal(t_ray ray, t_obj *obj, simd_float3 hit, \
	float dist_i)
{
	float		m;
	simd_float3	normalc;

	if (obj->id == TRIANGLE)
		return (trianglenormal(obj->type.triangle, ray.dir));
	else if (obj->id == SPHERE)
		return (simd_normalize((hit - obj->type.sphere->orig)));
	else if (obj->id == PLANE)
		return (planenormal(obj->type.plane, ray.dir));
	else if (obj->id == CYLINDER)
	{
		m = simd_dot(ray.dir, obj->type.cylinder->orient) * dist_i + \
			simd_dot(ray.orig - obj->type.cylinder->orig, \
			simd_normalize(obj->type.cylinder->orient));
		normalc = simd_normalize(hit - obj->type.cylinder->orig - \
			simd_normalize(obj->type.cylinder->orient) * m);
		return (cylindernormal(normalc, ray.dir));
	}
	else if (obj->id == SQUARE)
		return (squarenormal(obj->type.square->orient, ray.dir));
	return (vector3(0.f, 0.f, 0.f));
}
