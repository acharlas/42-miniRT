/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:16 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:18 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	*calculate_delta(t_ray ray, const t_cylinder cy, \
	float *x, float *y)
{
	float	a;
	float	b;
	float	c;
	float	delta;

	a = simd_dot(ray.dir, ray.dir) - powf(simd_dot(ray.dir, cy.orient), 2);
	b = 2 * (simd_dot(ray.dir, ray.orig - cy.orig) - (simd_dot(ray.dir,
		cy.orient) * simd_dot(ray.orig - cy.orig, cy.orient)));
	c = simd_dot(ray.orig - cy.orig, ray.orig - cy.orig) - powf(simd_dot(
		ray.orig - cy.orig, cy.orient), 2) - powf(cy.diameter / 2.f, 2);
	delta = powf(b, 2) - 4 * a * c;
	if (delta < 0)
		return (NULL);
	*x = (-b + sqrtf(delta)) / (a * 2);
	*y = (-b - sqrtf(delta)) / (a * 2);
	return (x);
}

float			ray_intersect_cylinder(t_ray ray, const t_cylinder cy)
{
	float	x;
	float	y;
	float	m1;
	float	m2;

	if (!(calculate_delta(ray, cy, &x, &y)))
		return (FLT_MAX);
	m1 = simd_dot(ray.dir, cy.orient) * x + simd_dot(ray.orig -
		cy.orig, simd_normalize(cy.orient));
	m2 = simd_dot(ray.dir, cy.orient) * y + simd_dot(ray.orig -
		cy.orig, simd_normalize(cy.orient));
	if ((m1 >= -cy.height / 2 && m1 <= cy.height / 2) &&
		(m2 >= -cy.height / 2 && m2 <= cy.height / 2))
	{
		if (x < y && x > 0)
			return (x);
		else if (y < x && y > 0)
			return (y);
	}
	if ((m1 > -cy.height / 2 && m1 < cy.height / 2) && x > 0)
		return (x);
	if ((m2 > -cy.height / 2 && m2 < cy.height / 2) && y > 0)
		return (y);
	return (FLT_MAX);
}

t_obj			*make_cylinder(simd_float3 orig, simd_float3 orient, \
	simd_float3 color, float dh[2])
{
	t_cylinder	*cy;
	t_obj		*cy_o;

	cy = p_malloc(sizeof(t_cylinder), 1, "cylinder");
	cy_o = p_malloc(sizeof(t_obj), 0, "cylinder");
	cy->orig = orig;
	cy->orient = orient;
	cy->diameter = dh[0];
	cy->height = dh[1];
	cy_o->id = CYLINDER;
	cy_o->type.cylinder = cy;
	cy_o->color = color;
	return (cy_o);
}

void			add_cylinder(char **info, t_scene *scene)
{
	t_obj		*cy;
	simd_float3	orig;
	simd_float3	orient;
	simd_float3	color;
	float		dh[2];

	if (ft_stralen(info) != 6)
		error_handling(BAD_NB_PARAM, "cylinder", "");
	orig = make_coord(info[1], "cylinder");
	orient = make_orient(info[2], "cylinder");
	color = make_color(info[5], "cylinder");
	if (!ft_is_floatstr(info[3]) || !ft_is_floatstr(info[4]))
		error_handling(INVALID_VALUE, "cylinder", " height | diameter");
	dh[0] = ft_simple_atof(info[3]);
	if (dh[0] <= 0)
		error_handling(OUT_OF_RANGE, "cylinder", " diameter");
	dh[1] = ft_simple_atof(info[4]);
	if (dh[1] <= 0)
		error_handling(OUT_OF_RANGE, "cylinder", " height");
	cy = make_cylinder(orig, orient, color, dh);
	ft_lstadd_front(&scene->listobj, ft_lstnew(cy));
}
