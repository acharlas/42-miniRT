/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:51 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:52 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/resource.h>
#include <stdio.h>

float	radians(float degrees)
{
	return (degrees * M_PI / 180);
}

t_list	*g_alloc_lst = NULL;
t_scene	*g_scene = NULL;

int		main(int ac, char **av)
{
	if (ac <= 1)
		error_handling(BAD_NB_PARAM, "miniRT Program", "");
	g_scene = build_rt(av[1]);
	if (g_scene)
	{
		if (ac > 2 && ft_strncmp(av[2], "-save", 5) == 0)
		{
			g_scene->rend = SAVETOFILE;
			render(g_scene);
			cleanup(0);
			return (0);
		}
		g_scene->rend = TORENDER;
		g_scene->win_ptr = mlx_new_window(g_scene->mlx_ptr, g_scene->width,\
				g_scene->height, "miniRT");
		mlx_key_hook(g_scene->win_ptr, deal_key, g_scene);
		mlx_loop_hook(g_scene->mlx_ptr, render, g_scene);
		mlx_hook(g_scene->win_ptr, DestroyNotify, StructureNotifyMask, \
			close_mlx, g_scene);
		mlx_hook(g_scene->win_ptr, 15, (1LL << 16), handle_mini, g_scene);
		mlx_loop(g_scene->mlx_ptr);
	}
	cleanup(0);
	return (0);
}
