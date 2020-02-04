/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:16:37 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 08:29:54 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene		scene_intersect(t_ray ray, const t_list *listobj)
{
	float	dist_i = FLT_MAX;
	t_obj	*closest = NULL;
	float	temp_dist;
	t_scene out;
	bool	hit_obj = false;

	while (listobj)
	{
		
		temp_dist = ray_intersect(ray, listobj->obj);
		if (temp_dist < dist_i)
		{
			dist_i = temp_dist;
			closest = listobj->obj;
			hit_obj = true;
		}
		listobj = listobj->next;
	}
	if (dist_i == FLT_MAX)
	{
		out.hit = c_vect3f(0, 0, 0);
		out.normal = c_vect3f(0, 0, 0);
		out.material.color = c_vect3f(0.62, 0.95, 0.99);
		out.material.specular_expo = 0;
		out.material.refractive_index = 0;
		out.material.albedo = c_vect4f(0,0,0,0);
		out.material.refractive_index = 0;
		out.material.specular_expo = 0;
	}
	else
	{
			out.hit = v_plus(ray.orig, v_mult(ray.dir, dist_i));
			out.normal = get_normal(ray, closest, out.hit, dist_i);
			out.material = closest->material;
	}
	return (out);
}

