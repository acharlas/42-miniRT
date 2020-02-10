/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cast_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:18:31 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/10 13:37:31 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <string.h>

void	cast_ray_thread(void *argus)
{
	t_args *args = (t_args *)argus;
	__m128 vue = _mm_setr_ps((args->x + 0.5) - Width / 2, - (args->y + 0.5) + Height / 2, - Height / (2. * tan(FOV / 2.)), 0.);
	t_ray ray = {_mm_setr_ps(0, 0, 0, 0), normalize(vue)};
	*args->pixel = color_to_int(cast_ray(ray, args->par->listobj, args->par->listlight, 0));
	printf("rendering for pixels : %d - %d\n", args->x , args->y);
	fflush(stdout);
}

__m128	reflected_color(__m128 *dir, const t_list *listobj, const t_list *listlight, t_scene scene, int depth)
{
	t_ray ree_ray;
	ree_ray.dir = normalize(reflect(*dir, scene.normal));
	ree_ray.orig = v_dot(ree_ray.dir, scene.normal) < 0 ? v_minus(scene.hit, v_mult(scene.normal, 0.001)) : v_plus(scene.hit, v_mult(scene.normal, 0.001));
	//ree_ray.depth = ++(ray->depth);
	return 	(cast_ray(ree_ray, listobj, listlight, depth + 1));
}

__m128	refracted_color(__m128 *dir, const t_list *listobj, const t_list *listlight, t_scene scene, int depth)
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

//__m128	all_color_add(const t_list *listlight)
//{
//	int		nol;
//	__m128	color;
//
//	nol = ft_lstsize(listlight);
//	color = _mm_setzero_ps();
//	while (listlight)
//	{
//		color = v_plus(color, v_mult(LIGHT->color, 1/nol));
//		listlight = listlight->next;
//	}
//	color = verif_color(color);
//	return (color);
//}

__m128	cast_ray(t_ray ray, const t_list *listobj, const t_list *listlight, int depth)
{
	__m128	add_color;
	float diffuse_light_intensity = 0.;
	float specular_light_intensity = 0.;
	__m128			refract_col;
	__m128			reflect_col;	
	t_scene			scene;
	t_scene			scene_shadow;
	__m128			color;
	t_ray 			shadow;
	__m128			tmp_vec = _mm_setzero_ps();
	const __m128	initial_dir = ray.dir;

	scene = scene_intersect(ray, listobj);
	if (depth > 4 || (memcmp(&scene.hit, &tmp_vec, sizeof(__m128)) == 0))
		return (_mm_setr_ps(0.62, 0.95, 0.99, 0.));
	//add_color = all_color_add(listlight); // C moch
	add_color = _mm_setr_ps(1, 1, 1, 0);
	refract_col = refracted_color(&ray.dir, listobj, listlight, scene, depth);
	reflect_col = reflected_color(&ray.dir, listobj, listlight, scene, depth);
	while (listlight)
	{
		ray.dir = normalize(v_minus(LIGHT->pos, scene.hit));
		shadow = make_shadow_ray(ray, scene);
		scene_shadow = scene_intersect(shadow, listobj);
		if ((memcmp(&scene_shadow.hit, &tmp_vec, sizeof(__m128)) == 0))
		{
			diffuse_light_intensity += LIGHT->intensity * maxf(0., v_dot(ray.dir, scene.normal));
			specular_light_intensity += powf(maxf(0., v_dot(reflect(ray.dir, scene.normal), initial_dir)), scene.material.specular_expo) * LIGHT->intensity;
		}
		listlight = listlight->next;
	}
	ray.dir = initial_dir;
	color = v_plus(v_plus(v_plus(v_mult(scene.material.color, (diffuse_light_intensity * scene.material.albedo.i)), v_mult(add_color,(specular_light_intensity * scene.material.albedo.j))),v_mult(reflect_col, scene.material.albedo.k)),v_mult(refract_col, scene.material.albedo.l));
	return (color);
}
