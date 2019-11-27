/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_create.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:54:43 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/27 20:10:22 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	c_light(t_list **alst, vect3f pos, vect3f color, float intensity)
{
	t_light *light;

	light = malloc(sizeof(t_light));
	light->pos = pos;
	light->intensity = intensity;
	light->color = color;
	ft_lstadd_front(alst, ft_lstnew(light, 'l'));
}

void	c_sphere(t_list **alst, vect3f pos, t_material material, float r, void *f)
{
	t_sphere *sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->pos = pos;
	sphere->r = r;
	sphere->material.refractive_index = material.refractive_index;
	sphere->material.color = material.color; // bg_color(210, 51, 108);
	sphere->material.albedo = material.albedo; // albedo[0] : diffuse light | albedo[1] : specular light | albedo[2] : reflect light
	sphere->material.specular_expo = material.specular_expo;
	sphere->ray_intersect = f;
	ft_lstadd_front(alst, ft_lstnew(sphere, 's'));
}

t_material 	c_material(vect3f color, vect4f albedo, float refrac_ind, float spec_expo)
{
	t_material material;

	material.color = color;
	material.albedo = albedo;
	material.refractive_index = refrac_ind;
	material.specular_expo = spec_expo;
	return (material);
}