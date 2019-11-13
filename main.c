/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/07 19:19:55 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include "miniRT.h"

int main(void)
{
    int i;
    int j;
	t_sphere sphere;
	long distance;
	int color = 0xFFFFFF;

	sphere.r = 127;
	sphere.x = 250;
	sphere.y = 250;
	void *mlx = mlx_init();
	void *mlxwindow = mlx_new_window(mlx, 500, 500, "yes");
	i = 0;
	while(i <= 750)
	{
		j = 0;
		while(j <= 1334)
		{
			distance = sqrt((double)(i - sphere.x)*(i - sphere.x) + (j - sphere.y)*(j - sphere.y));
			if (distance < sphere.r)
			{
				mlx_pixel_put(mlx, mlxwindow, i, j, color);
				color = color - 0x000001;
			}
			j++;
		}
		i++;
	}
	mlx_loop(mlx);
}