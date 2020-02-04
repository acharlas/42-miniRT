/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cast_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:18:31 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 08:29:07 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <string.h>

vect3f	reflected_color(t_ray *ray, const t_list *listobj, const t_list *listlight, t_scene scene)
{
	t_ray ree_ray;
	ree_ray.dir = normalize(reflect(ray->dir, scene.normal));
	ree_ray.orig = v_dot(ree_ray.dir, scene.normal) < 0 ? v_minus(scene.hit, v_mult(scene.normal, 0.001)) : \
	v_plus(scene.hit, v_mult(scene.normal, 0.001));
	ree_ray.depth = ray->depth + 1;
	return 	(cast_ray(ree_ray, listobj, listlight));
}

vect3f	refracted_color(t_ray *ray, const t_list *listobj, const t_list *listlight, t_scene scene)
{
	t_ray rea_ray;
	rea_ray.dir = normalize(refract(ray->dir, scene.normal, scene.material.refractive_index, 1.0));
	rea_ray.orig = v_dot(rea_ray.dir, scene.normal) < 0 ? v_minus(scene.hit, v_mult(scene.normal, 0.001)) :
	v_plus(scene.hit, v_mult(scene.normal, 0.001));
	rea_ray.depth = ray->depth + 1;
	return 	(cast_ray(rea_ray, listobj, listlight));
}

t_ray	shadow_ray(t_ray ray, t_scene scene)
{
	t_ray shadow_ray;

	shadow_ray.orig = v_dot(ray.dir, scene.normal) < 0 ? v_minus(scene.hit, v_mult(scene.normal, 0.01)) : \
	v_plus(scene.hit, v_mult(scene.normal, 0.01));
	shadow_ray.dir = ray.dir;
	shadow_ray.depth = 0;
	return (shadow_ray);
}

vect3f	all_color_add(const t_list *listlight)
{
	int		nol;
	vect3f	color;

	nol = ft_lstsize(listlight);
	color = c_vect3f(0, 0, 0);
	while (listlight)
	{
		color = v_plus(color, v_div(LIGHT->color, nol));
		listlight = listlight->next;
	}
	color = verif_color(color);
	return (color);
}

vect3f	cast_ray(t_ray ray, const t_list *listobj, const t_list *listlight)
{
	vect3f	add_color;
	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	vect3f			refract_col;
	vect3f			reflect_col;	
	t_scene			scene;
	t_scene			scene_shadow;
	vect3f			color;
	t_ray 			shadow;
	vect3f			tmp_vec = c_vect3f(0,0,0);

	scene = scene_intersect(ray, listobj);
	if (ray.depth > 4 || (memcmp(&scene.hit, &tmp_vec, sizeof(vect3f)) == 0))
		return (c_vect3f(0.62, 0.95, 0.99));
	// add_color = all_color_add(listlight); // C moch
	add_color = c_vect3f(1,1,1);
	while (listlight)
	{
		ray.dir = normalize(v_minus(LIGHT->pos, scene.hit));

		shadow = shadow_ray(ray, scene);
		scene_shadow = scene_intersect(shadow, listobj);
		if ((memcmp(&scene_shadow.hit, &tmp_vec, sizeof(vect3f)) == 0))
		{
			diffuse_light_intensity += LIGHT->intensity * maxf(0.f, v_dot(ray.dir, scene.normal));
			specular_light_intensity += powf(maxf(0.f, v_dot(reflect(ray.dir, scene.normal), ray.dir)), scene.material.specular_expo) * LIGHT->intensity;
		}
		listlight = listlight->next;
	}
	//color = c_vect3f(0.62, 0.95, 0.99);
	color = v_plus(v_plus(v_plus(v_mult(scene.material.color, (diffuse_light_intensity * scene.material.albedo.i)), v_mult(add_color,(specular_light_intensity * scene.material.albedo.j))),v_mult(refracted_color(&ray, listobj, listlight, scene), scene.material.albedo.k)),v_mult(refracted_color(&ray, listobj, listlight, scene), scene.material.albedo.l));
	return (color);
}
