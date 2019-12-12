/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_create.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:54:43 by acharlas          #+#    #+#             */
/*   Updated: 2019/12/04 18:50:26 by acharlas         ###   ########.fr       */
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
	ft_lstadd_front(alst, ft_lstnew(light, "l"));
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

void	c_sphere(t_list **alst, vect3f pos, t_material material, float r)
{
	t_sphere *sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->pos = pos;
	sphere->r = r;
	sphere->material = material;
	sphere->material.specular_expo = material.specular_expo;
	sphere->ray_intersect = ray_intersect_sphere;
	ft_lstadd_front(alst, ft_lstnew(sphere, "sp"));
}

void	c_cylinder(t_list **alst, vect3f pos, vect3f rot ,t_material material, float r, float h)
{
	t_cylinder *cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->pos = pos;
	cylinder->h = h;
	cylinder->material = material;
	cylinder->r = r;
	cylinder->rot = rot;
	cylinder->ray_intersect = ray_intersect_cylinder;
	ft_lstadd_front(alst, ft_lstnew(cylinder, "cy"));
}

void	c_plane(t_list **alst, vect3f pos, vect3f rot ,t_material material)
{
	t_plane *plane;

	plane = malloc(sizeof(t_plane));
	plane->pos = pos;
	plane->material = material;
	plane->rot = rot;
	plane->ray_intersect = ray_intersect_plane;
	ft_lstadd_front(alst, ft_lstnew(plane, "pl"));
}

void	c_cone(t_list **alst, vect3f pos, vect3f rot ,t_material material, float angle)
{
	t_cone *cone;

	cone = malloc(sizeof(t_cone));
	cone->pos = pos;
	cone->material = material;
	cone->rot = rot;
	cone->a = angle;
	cone->ray_intersect = ray_intersect_cone;
	ft_lstadd_front(alst, ft_lstnew(cone, "co"));
}

void	c_triangle(t_list **alst, vect3f c1, vect3f c2, vect3f c3,t_material material)
{
	t_triangle *triangle;

	triangle = malloc(sizeof(t_triangle));
	triangle->c1 = c1;
	triangle->c2 = c2;
	triangle->c3 = c3;
	triangle->material = material;
	triangle->ray_intersect = ray_intersect_triangle;
	ft_lstadd_front(alst, ft_lstnew(triangle, "tr"));
}
