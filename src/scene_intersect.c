/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:34 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:35 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj		*scene_intersect(t_ray ray, const t_list *listobj, \
	simd_float3 *hit, float *dist_i)
{
	float	temp_dist;
	t_obj	*closest;

	closest = NULL;
	*dist_i = FLT_MAX;
	while (listobj)
	{
		if (((temp_dist = ray_intersect(ray, listobj->content)) < *dist_i))
		{
			*dist_i = temp_dist;
			closest = listobj->content;
		}
		listobj = listobj->next;
	}
	if (closest && hit)
		*hit = ray.orig + ray.dir * *dist_i;
	return (closest);
}
