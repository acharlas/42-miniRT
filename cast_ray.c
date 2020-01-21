/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:18:31 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 21:09:31 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	c_ree_rea(t_ray	*ray, const vect3f *dir,const t_list *listobj,const t_list *listlight)
{
	ray->rea.dir = normalize(refract(dir, &ray->base.n, ray->base.material.refractive_index, 1.0));
	ray->rea.orig = v_dot(ray->rea.dir, ray->base.n) < 0 ? v_minus(ray->base.pt, v_mult(ray->base.n, 0.001)) : v_plus(ray->base.pt, v_mult(ray->base.n, 0.001));
	ray->rea.color = cast_ray(ray->rea.orig, ray->rea.dir, listobj, listlight, ray->depth + 1);

	ray->ree.dir = normalize(reflect(dir, &ray->base.n));
	ray->ree.orig = v_dot(ray->ree.dir, ray->base.n) < 0 ? v_minus(ray->base.pt, v_mult(ray->base.n, 0.001)) : v_plus(ray->base.pt, v_mult(ray->base.n, 0.001));
	ray->ree.color = cast_ray(ray->ree.orig, ray->ree.dir, listobj, listlight, (ray->depth + 1));
}


vect3f	cast_ray(const vect3f orig, const vect3f dir, const t_list *listobj, const t_list *listlight, size_t depth)
{
	float	diffuse_light_intensity;
	float	specular_light_intensity;
	t_ray	ray;
	vect3f	add_color = c_vect3f(0, 0, 0);
	
	ray.depth = depth;
	if (ray.depth > 4 || !scene_intersect(&orig, &dir, listobj, &ray.base.pt, &ray.base.n, &ray.base.material))
		return (c_vect3f(0.78, 0.74, 0.76)); //bg_color(200,120,255));
	c_ree_rea(&ray, &dir, listobj, listlight);
	diffuse_light_intensity = 0;
	specular_light_intensity = 0;
	while (listlight)
	{
		ray.base.dir = normalize(v_minus(LIGHT->pos, ray.base.pt));
		float light_distance = norm(v_minus(LIGHT->pos, ray.base.pt));

		ray.sdw.orig = v_dot(ray.base.dir, ray.base.n) < 0 ? v_minus(ray.base.pt, v_mult(ray.base.n, 0.001)) : v_plus(ray.base.pt, v_mult(ray.base.n, 0.001));
		ray.sdw.pt = c_vect3f(0, 0, 0);
		ray.sdw.n = c_vect3f(0, 0, 0);

		t_material tmpmaterial;
		add_color = v_plus(add_color, v_div(LIGHT->color, ft_lstsize(listlight)));
		add_color = verif_color(add_color);
		if (scene_intersect(&ray.sdw.orig, &ray.base.dir, listobj, &ray.sdw.pt, &ray.sdw.n, &tmpmaterial) && (norm(v_minus(ray.sdw.pt, ray.sdw.orig))) < light_distance)
		{
			listlight = listlight->next;
		 	continue;
		}
		diffuse_light_intensity += LIGHT->intensity * maxf(0.f, v_dot(ray.base.dir, ray.base.n));
		specular_light_intensity += powf(maxf(0.f, v_dot(reflect(&ray.base.dir, &ray.base.n), dir)), ray.base.material.specular_expo) * LIGHT->intensity;
		listlight = listlight->next;
	}
	ray.base.color = v_multv(v_plus(v_plus(v_plus(v_mult(ray.base.material.color, (diffuse_light_intensity * ray.base.material.albedo.i)), v_mult(add_color,(specular_light_intensity * ray.base.material.albedo.j))),v_mult(ray.ree.color, ray.base.material.albedo.k)),v_mult(ray.rea.color, ray.base.material.albedo.l)), add_color);
	ray.base.color = verif_color(ray.base.color);
	return (ray.base.color);
}