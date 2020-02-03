/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:16:37 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/03 15:40:17 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene		scene_intersect(t_ray ray, const t_list *listobj)
{
	float	dist_i;
	t_obj	closest;
	float	temp_dist;
	t_scene out;

	while (listobj)
	{
		
		temp_dist = ray_intersect(ray, &dist_i, listobj->obj);
		if (temp_dist < dist_i)
		{
			dist_i = temp_dist;
			closest = *(t_obj *)listobj->obj;
		}
		listobj = listobj->next;
	}
	out.hit = v_plus(ray.orig, v_mult(ray.dir, dist_i));
	out.normal = get_normal(ray, &closest, out.hit, dist_i);
	out.material = closest.material;
	if (dist_i == FLT_MAX)
	{
		out.hit = c_vect3f(0, 0, 0);
		out.normal = c_vect3f(0, 0, 0);
		out.material.color = c_vect3f(0.62, 0.95, 0.99);
	}
	return (out);
}
