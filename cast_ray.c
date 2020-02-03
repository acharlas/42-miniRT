/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:18:31 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/03 08:46:51 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	c_ree_rea(t_ray *ray, const vect3f *dir, \
const t_list *listobj, const t_list *listlight)
{
	ray->rea.dir = normalize(refract(dir, &ray->base.n, \
	ray->base.material.refractive_index, 1.0));
	ray->rea.orig = v_dot(ray->rea.dir, ray->base.n) < 0 ? \
	v_minus(ray->base.pt, v_mult(ray->base.n, 0.001)) : \
	v_plus(ray->base.pt, v_mult(ray->base.n, 0.001));
	ray->rea.color = cast_ray(ray->rea.orig, ray->rea.dir, \
	listobj, listlight, ray->depth + 1);
	ray->ree.dir = normalize(reflect(dir, &ray->base.n));
	ray->ree.orig = v_dot(ray->ree.dir, ray->base.n) < 0 ? \
	v_minus(ray->base.pt, v_mult(ray->base.n, 0.001)) : \
	v_plus(ray->base.pt, v_mult(ray->base.n, 0.001));
	ray->ree.color = cast_ray(ray->ree.orig, ray->ree.dir, \
	listobj, listlight, (ray->depth + 1));
}

void	cast_shadows(t_ray *ray)
{
	ray->sdw.orig = v_dot(ray->base.dir, ray->base.n) < 0 ? \
	v_minus(ray->base.pt, v_mult(ray->base.n, 0.001)) : \
	v_plus(ray->base.pt, v_mult(ray->base.n, 0.001));
	ray->sdw.pt = c_vect3f(0, 0, 0);
	ray->sdw.n = c_vect3f(0, 0, 0);
}

vect3f	all_color_add(const t_list *light)
{
	int		nol;
	vect3f	color;

	nol = ft_lstsize(light);
	color = c_vect3f(0, 0, 0);
	while (light)
	{
		color = v_plus(color, v_div(((t_light *)(light->data))->color, nol));
		light = light->next;
	}
	color = verif_color(color);
	return (color);
}

vect3f	cast_ray(const vect3f orig, const vect3f dir, const t_list *listobj, const t_list *listlight, size_t depth)
{
	t_ray	ray;
	vect3f	add_color;
	t_material	tmpmaterial;
	
	ray.depth = depth;
	add_color = all_color_add(listlight);
	if (ray.depth > 4 || !scene_intersect(&orig, &dir, listobj, &ray.base.pt, &ray.base.n, &ray.base.material))
		return (c_vect3f(0.62, 0.95, 0.99));
	c_ree_rea(&ray, &dir, listobj, listlight);
	ray.dli = 0;
	ray.sli = 0;
	while (listlight)
	{
		ray.base.dir = normalize(v_minus(LIGHT->pos, ray.base.pt));
		ray.ld = norm(v_minus(LIGHT->pos, ray.base.pt));
		cast_shadows(&ray);
		if (scene_intersect(&ray.sdw.orig, &ray.base.dir, listobj, &ray.sdw.pt, &ray.sdw.n, &tmpmaterial) && (norm(v_minus(ray.sdw.pt, ray.sdw.orig))) < ray.ld)
		{
			listlight = listlight->next;
		 	continue;
		}
		ray.dli += LIGHT->intensity * maxf(0.f, v_dot(ray.base.dir, ray.base.n));
		ray.sli += powf(maxf(0.f, v_dot(reflect(&ray.base.dir, &ray.base.n), dir)), ray.base.material.specular_expo) * LIGHT->intensity;
		listlight = listlight->next;
	}
	ray.base.color = v_multv(v_plus(v_plus(v_plus(v_mult(ray.base.material.color, (ray.dli * ray.base.material.albedo.i)), v_mult(add_color,(ray.sli * ray.base.material.albedo.j))),v_mult(ray.ree.color, ray.base.material.albedo.k)),v_mult(ray.rea.color, ray.base.material.albedo.l)), add_color);
	ray.base.color = verif_color(ray.base.color);
	return (ray.base.color);
}
