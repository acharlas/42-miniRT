/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_create.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:54:43 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 11:51:12 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	c_cylinder(t_list **alst, vect3f pos, vect3f rot ,t_material material, float r, float h)
{
	t_cylinder *cylinder;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	cylinder = malloc(sizeof(t_cylinder));
	cylinder->pos = pos;
	cylinder->h = h;
	cylinder->r = r;
	cylinder->rot = rot;
	obj->data = cylinder;
	obj->type = 'c';
	obj->material = material;
	ft_lstadd_front(alst, ft_lstnew(obj));
}

void	c_plane(t_list **alst, vect3f pos, vect3f rot ,t_material material)
{
	t_plane *plane;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	plane = malloc(sizeof(t_plane));
	plane->pos = pos;
	plane->rot = rot;
	obj->data = plane;
	obj->material = material;
	obj->type = 'p';
	ft_lstadd_front(alst, ft_lstnew(obj));
}

void	c_cone(t_list **alst, vect3f pos, vect3f rot ,t_material material, float angle)
{
	t_cone *cone;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	cone = malloc(sizeof(t_cone));
	cone->pos = pos;
	cone->rot = rot;
	cone->a = angle;
	obj->data = cone;
	obj->material = material;
	obj->type = 'k';

	ft_lstadd_front(alst, ft_lstnew(obj));
}


void	c_triangle(t_list **alst, vect3f c1, vect3f c2, vect3f c3,t_material material)
{
	t_triangle *triangle;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	triangle = malloc(sizeof(t_triangle));
	triangle->c1 = c1;
	triangle->c2 = c2;
	triangle->c3 = c3;
	obj->data = triangle;
	obj->material = material;
	obj->type = 't';
	ft_lstadd_front(alst, ft_lstnew(obj));
}

void	c_sphere(t_list **alst, vect3f pos, t_material material, float r)
{
	t_sphere *sphere;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	sphere = malloc(sizeof(t_sphere));
	sphere->pos = pos;
	sphere->r = r;
	obj->data = sphere;
	obj->material = material;
	obj->material.specular_expo = material.specular_expo;
	obj->type = 's';
	ft_lstadd_front(alst, ft_lstnew(obj));
}
