/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:40 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:42 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		set_resolution(char **info, t_scene *scene)
{
	int	width;
	int	height;
	int	screen_dim[2];

	if (ft_stralen(info) != 3)
		error_handling(BAD_NB_PARAM, "resolution", "");
	if (!ft_is_digitstr(info[1]) || !ft_is_digitstr(info[2]))
		error_handling(INVALID_VALUE, "resolution", "");
	mlx_get_screen_size(scene->mlx_ptr, &screen_dim[0], &screen_dim[1]);
	if (scene->width != 0 || scene->height != 0)
		error_handling(ALREADY_SET, "resolution");
	width = ft_atoi(info[1]);
	height = ft_atoi(info[2]);
	if (width <= 0 || height <= 0)
		error_handling(OUT_OF_RANGE, "resolution", "");
	scene->width = MIN(width, screen_dim[0]);
	scene->height = MIN(height, screen_dim[1]);
}

t_scene		*verify_scene(t_scene *scene)
{
	if (ft_lstsize(scene->listcam) == 0)
		error_handling(INVALID_VALUE, ".rt file : Missing camera", "");
	if (scene->height == 0 || scene->width == 0)
		error_handling(INVALID_VALUE, ".rt file : Invalid resolution", "");
	if (!scene->amlight)
		error_handling(INVALID_VALUE, ".rt file : Missing ambient light", "");
	return (scene);
}

t_scene		*scene_init(void)
{
	t_scene	*scene;

	scene = p_malloc(sizeof(t_scene), 1, "scene");
	scene->height = 0;
	scene->width = 0;
	scene->mlx_ptr = mlx_init();
	scene->win_ptr = NULL;
	scene->listobj = NULL;
	scene->listlight = NULL;
	scene->listcam = NULL;
	scene->amlight = NULL;
	return (scene);
}

void		build_scene(t_scene *scene, char **info)
{
	if (*info && ft_strcmp(info[0], "R") == 0)
		set_resolution(info, scene);
	if (*info && ft_strcmp(info[0], "sp") == 0)
		add_sphere(info, scene);
	if (*info && ft_strcmp(info[0], "pl") == 0)
		add_plane(info, scene);
	if (*info && ft_strcmp(info[0], "tr") == 0)
		add_triangle(info, scene);
	if (*info && ft_strcmp(info[0], "sq") == 0)
		add_square(info, scene);
	if (*info && ft_strcmp(info[0], "cy") == 0)
		add_cylinder(info, scene);
	if (*info && ft_strcmp(info[0], "c") == 0)
		add_camera(info, scene);
	if (*info && ft_strcmp(info[0], "l") == 0)
		add_light(info, scene);
	if (*info && ft_strcmp(info[0], "A") == 0)
		add_ambientlight(info, scene);
}
