/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:16:37 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/23 17:22:34 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		scene_intersect(const vect3f *orig, const vect3f *dir, const t_list *listobj, vect3f *hit, vect3f *n, t_material *material)
{
	float	dist_i;
	float	m;
	float	k;
	t_dist	t_dist;

	t_dist = init_dist();
	while (listobj)
	{
		if (ft_strncmp(listobj->name, "tr", 2) == 0)
		{
			if(TRIANGLE->ray_intersect(orig, dir, &dist_i, *TRIANGLE) && calcule_dist(dist_i, t_dist))
			{
				t_dist.tr_dist = dist_i;
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize(v_cross(v_minus(TRIANGLE->c1, TRIANGLE->c2),v_minus(TRIANGLE->c1, TRIANGLE->c3)));
				*material = TRIANGLE->material;
			}
		}
		else if (ft_strncmp(listobj->name, "cy", 2) == 0)
		{
			if(CYLINDER->ray_intersect(orig, dir, &dist_i, *CYLINDER) && calcule_dist(dist_i, t_dist))
			{
				t_dist.cy_dist = dist_i;
				m = v_dot(*dir, normalize(CYLINDER->rot)) * dist_i + v_dot(v_minus(*orig, CYLINDER->pos),normalize(CYLINDER->rot));
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize((v_minus(v_minus(*hit,CYLINDER->pos), v_mult(normalize(CYLINDER->rot), m))));
				*material = CYLINDER->material;
			}
		}
		else if(ft_strncmp(listobj->name, "pl", 2) == 0)
		{
			if(PLANE->ray_intersect(orig, dir, &dist_i, *PLANE) && calcule_dist(dist_i, t_dist))
			{
				t_dist.pl_dist = dist_i;
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize(PLANE->rot);
				*material = PLANE->material;
			}
		}
		else if(ft_strncmp(listobj->name, "sp", 2) == 0)
		{
			if (SPHERE->ray_intersect(orig, dir, &dist_i, *SPHERE) && calcule_dist(dist_i, t_dist))
			{
				t_dist.sp_dist = dist_i;
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize(v_minus(*hit, SPHERE->pos));
				*material = SPHERE->material;
			}
		}
		else if(ft_strncmp(listobj->name, "co", 2) == 0)
		{
			if (CONE->ray_intersect(orig, dir, &dist_i, *CONE) && calcule_dist(dist_i, t_dist))
			{
				t_dist.co_dist = dist_i;
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				k = tan(((CONE->a / 2) * M_PI) / 180);
				m = v_dot(*dir, normalize(CYLINDER->rot)) * dist_i + v_dot(v_minus(*orig, CYLINDER->pos),normalize(CYLINDER->rot));
				*n = normalize((v_minus(v_minus(*hit,CYLINDER->pos), v_mult(v_mult(normalize(CYLINDER->rot), m), 1+k*k))));
				*material = CONE->material;
			}
		}
		listobj = listobj->next;
	}
	return (minimumfloat(5 , t_dist.pl_dist, t_dist.sp_dist, t_dist.cy_dist, t_dist.co_dist, t_dist.tr_dist) < 100);
}