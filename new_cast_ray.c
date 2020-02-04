/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cast_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:18:31 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 13:32:43 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <string.h>

vect3f	reflected_color(vect3f *dir, const t_list *listobj, const t_list *listlight, t_scene scene, int depth)
{
	t_ray ree_ray;
	ree_ray.dir = normalize(reflect(*dir, scene.normal));
	ree_ray.orig = v_dot(ree_ray.dir, scene.normal) < 0 ? v_minus(scene.hit, v_mult(scene.normal, 0.001)) : v_plus(scene.hit, v_mult(scene.normal, 0.001));
	//ree_ray.depth = ++(ray->depth);
	return 	(cast_ray(ree_ray, listobj, listlight, depth + 1));
}

vect3f	refracted_color(vect3f *dir, const t_list *listobj, const t_list *listlight, t_scene scene, int depth)
{
	t_ray rea_ray;
	rea_ray.dir = normalize(refract(*dir, scene.normal, scene.material.refractive_index, 1.0));
	rea_ray.orig = v_dot(rea_ray.dir, scene.normal) < 0 ? v_minus(scene.hit, v_mult(scene.normal, 0.001)) : v_plus(scene.hit, v_mult(scene.normal, 0.001));
	//rea_ray.depth = ++(ray->depth);
	return 	(cast_ray(rea_ray, listobj, listlight, depth + 1));
}

t_ray	make_shadow_ray(t_ray ray, t_scene scene)
{
	t_ray shadow_ray;

	shadow_ray.orig = v_dot(ray.dir, scene.normal) < 0 ? v_minus(scene.hit, v_mult(scene.normal, 0.001)) : \
	v_plus(scene.hit, v_mult(scene.normal, 0.001));
	shadow_ray.dir = ray.dir;
	//shadow_ray.depth = 0;
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

vect3f	cast_ray(t_ray ray, const t_list *listobj, const t_list *listlight, int depth)
{
	vect3f	add_color;
	float diffuse_light_intensity = 0.;
	float specular_light_intensity = 0.;
	vect3f			refract_col;
	vect3f			reflect_col;	
	t_scene			scene;
	t_scene			scene_shadow;
	vect3f			color;
	t_ray 			shadow;
	vect3f			tmp_vec = c_vect3f(0,0,0);
	const vect3f	initial_dir = ray.dir;
	const t_list			*initial_listlight = listlight;

	scene = scene_intersect(ray, listobj);
	if (depth > 1 || (memcmp(&scene.hit, &tmp_vec, sizeof(vect3f)) == 0))
		return (c_vect3f(0.62, 0.95, 0.99));
	//add_color = all_color_add(listlight); // C moch
	add_color = c_vect3f(1,1,1);
	while (listlight)
	{
		ray.dir = normalize(v_minus(LIGHT->pos, scene.hit));

		shadow = make_shadow_ray(ray, scene);
		scene_shadow = scene_intersect(shadow, listobj);
		if ((memcmp(&scene_shadow.hit, &tmp_vec, sizeof(vect3f)) == 0))
		{
			diffuse_light_intensity += LIGHT->intensity * maxf(0., v_dot(ray.dir, scene.normal));
			specular_light_intensity += powf(maxf(0., v_dot(reflect(ray.dir, scene.normal), initial_dir)), scene.material.specular_expo) * LIGHT->intensity;
		}
		listlight = listlight->next;
	}
	ray.dir = initial_dir;
	refract_col = refracted_color(&ray.dir, listobj, initial_listlight, scene, depth);
	reflect_col = reflected_color(&ray.dir, listobj, initial_listlight, scene, depth);
	color = v_plus(v_plus(v_plus(v_mult(scene.material.color, (diffuse_light_intensity * scene.material.albedo.i)), v_mult(add_color,(specular_light_intensity * scene.material.albedo.j))),v_mult(reflect_col, scene.material.albedo.k)),v_mult(refract_col, scene.material.albedo.l));
	return (color);
}
