/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:09 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:10 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ray_intersect(t_ray ray, t_obj *obj)
{
	if (obj->id == SPHERE)
		return (ray_intersect_sphere(ray, *obj->type.sphere));
	else if (obj->id == PLANE)
		return (ray_intersect_plane(ray, *obj->type.plane));
	else if (obj->id == CYLINDER)
		return (ray_intersect_cylinder(ray, *obj->type.cylinder));
	else if (obj->id == SQUARE)
		return (ray_intersect_square(ray, *obj->type.square));
	else if (obj->id == TRIANGLE)
		return (ray_intersect_triangle(ray, *obj->type.triangle));
	return (FLT_MAX);
}
