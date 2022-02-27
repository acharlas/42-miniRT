/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:10:52 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 15:35:18 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*make_camera(simd_float3 orig, simd_float3 orient, float fov)
{
	t_camera	*camera;

	camera = p_malloc(sizeof(t_camera), 0, "camera");
	camera->orig = orig;
	camera->orient = orient;
	camera->fov = fov;
	return (camera);
}

void		add_camera(char **info, t_scene *scene)
{
	t_camera	*camera;
	simd_float3	orig;
	simd_float3	orient;
	float		fov;

	if (ft_stralen(info) != 4)
		error_handling(BAD_NB_PARAM, "camera", "");
	orig = make_coord(info[1], "camera");
	orient = make_orient(info[2], "camera");
	if (!ft_is_floatstr(info[3]))
		error_handling(INVALID_VALUE, "camera", "");
	fov = ft_simple_atof(info[3]);
	if (ft_simple_atof(info[3]) > 180 || ft_simple_atof(info[3]) < 0)
		error_handling(OUT_OF_RANGE, "camera", " fov");
	camera = make_camera(orig, orient, radians(fov));
	ft_lstadd_front(&scene->listcam, ft_lstnew(camera));
}
