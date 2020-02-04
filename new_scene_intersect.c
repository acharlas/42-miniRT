/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:16:37 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 15:47:16 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene		scene_intersect(t_ray ray, const t_list *listobj)
{
	float	dist_i = FLT_MAX;
	t_obj	*closest = NULL;
	float	temp_dist;
	t_scene out;

	while (listobj)
	{
		if (((temp_dist = ray_intersect(ray, listobj->obj)) < dist_i))
		{
			dist_i = temp_dist;
			closest = listobj->obj;
		}
		listobj = listobj->next;
	}
	if (dist_i == FLT_MAX || closest == NULL)
	{
		out.hit = _mm_setzero_ps();
		out.material.color = _mm_set_ps(0.62, 0.95, 0.99, 0.);
	}
	else
	{
			out.hit = v_plus(ray.orig, v_mult(ray.dir, dist_i));
			out.normal = get_normal(ray, closest, out.hit, dist_i);
			out.material = closest->material;
	}
	return (out);
}
