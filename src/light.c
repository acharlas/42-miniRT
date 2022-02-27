/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:45 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:46 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*make_light(simd_float3 orig, float i, simd_float3 color)
{
	t_light	*light;
	t_obj	*light_o;

	light = p_malloc(sizeof(t_light), 1, "light");
	light->orig = orig;
	light->i = i;
	light_o = p_malloc(sizeof(t_obj), 0, "light");
	light_o->id = LIGHT;
	light_o->type.light = light;
	light_o->color = color;
	return (light_o);
}

void	add_light(char **info, t_scene *scene)
{
	t_obj		*light;
	simd_float3	color;
	simd_float3	orig;
	float		i;

	if (ft_stralen(info) != 4)
		error_handling(BAD_NB_PARAM, "light", "");
	orig = make_coord(info[1], "light");
	color = make_color(info[3], "light");
	if (!ft_is_floatstr(info[2]))
		error_handling(INVALID_VALUE, "light", " intensity");
	i = ft_simple_atof(info[2]);
	if (i > 1.f || i < 0.f)
		error_handling(OUT_OF_RANGE, "light", " intensity");
	light = make_light(orig, i, color);
	ft_lstadd_front(&scene->listlight, ft_lstnew(light));
}

void	add_ambientlight(char **info, t_scene *scene)
{
	t_obj		*amlight;
	simd_float3	color;
	float		i;

	if (scene->amlight)
		error_handling(ALREADY_SET, "Ambientlight");
	if (ft_stralen(info) != 3)
		error_handling(BAD_NB_PARAM, "ambientlight", "");
	color = make_color(info[2], "ambientlight");
	if (!ft_is_floatstr(info[1]))
		error_handling(INVALID_VALUE, "ambientlight", " intensity");
	i = ft_simple_atof(info[1]);
	if (i > 1.f || i < 0.f)
		error_handling(OUT_OF_RANGE, "ambientlight", " intensity");
	amlight = make_light(0, i, color);
	scene->amlight = amlight;
}
