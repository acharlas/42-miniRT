/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:40 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:41 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	deal_key(int key, t_scene *scene)
{
	static t_list	*initial_cam = NULL;

	if (!initial_cam)
		initial_cam = scene->listcam;
	if (key == 65289)
	{
		if (scene->listcam->next)
			scene->listcam = scene->listcam->next;
		else
			scene->listcam = initial_cam;
		scene->rend = TORENDER;
	}
	if (key == 65307)
		close_mlx(scene);
	return (0);
}

int	close_mlx(t_scene *scene)
{
	(void)scene;
	cleanup(0);
	return (0);
}

int	handle_mini(t_scene *scene)
{
	scene->rend = TORENDER;
	return (0);
}
