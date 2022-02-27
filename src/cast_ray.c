/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:10:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:00 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <string.h>

t_ray		make_ray(simd_float3 origin, simd_float3 dir)
{
	return ((t_ray){origin, dir});
}

simd_float3	blinn_phong(simd_float3 hit, const t_list *listlight, \
		const t_list *listobj, simd_float3 *nodir)
{
	t_light		*light;
	simd_float3	light_feat[6];
	t_ray		shadow;
	float		shd_di;

	light_feat[4] = 0;
	light_feat[5] = 0;
	while (listlight)
	{
		light = ((t_obj *)listlight->content)->type.light;
		light_feat[0] = ((t_obj *)listlight->content)->color;
		light_feat[1] = simd_normalize(light->orig - hit);
		shadow = make_ray(hit + nodir[0] * 0.001, light_feat[1]);
		if (!(scene_intersect(shadow, listobj, NULL, &shd_di) && shd_di < \
					simd_length(light->orig - hit)))
		{
			light_feat[2] = simd_normalize(light_feat[1] + nodir[1]);
			light_feat[4] += simd_clamp(simd_dot(nodir[0], light_feat[1]), 0.f,\
					1.f) * light->i * light_feat[0];
			light_feat[5] += simd_clamp(powf(simd_dot(nodir[0], light_feat[2]),\
						100.f), 0.f, 1.f) * light->i * light_feat[0];
		}
		listlight = listlight->next;
	}
	return (light_feat[4] + light_feat[5]);
}

simd_float3	cast_ray(t_ray ray, const t_list *listobj, const t_list *listlight,\
		t_scene *scene)
{
	simd_float3	hit;
	simd_float3	color;
	float		dist_i;
	t_obj		*obj;
	simd_float3 diffspec;

	color = 0;
	if ((obj = scene_intersect(ray, listobj, &hit, &dist_i)))
	{
		color = obj->color;
		diffspec = blinn_phong(hit, listlight, listobj, \
				(simd_float3[]){get_normal(ray, obj, hit, dist_i), \
				simd_normalize(((t_camera *)(scene->listcam->content))->orig \
						- hit)});
		color = simd_clamp(color * (diffspec + scene->amlight->type.light->i \
					* scene->amlight->color), 0.f, 1.f);
	}
	return (color);
}
