/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/20 19:46:12 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "miniRT.h"

vect3f	*ft_fill(float a, float b, float c, vect3f *out)
{
	out->x = a;
	out->y = b;
	out->z = c;
	return (out);
}

int	ray_intersect()
{

}

int main(void)
{
	int width = 500;
	int height = 500;
	t_sphere sphere;
	vect3f *framebuffer[width][height];

	void *mlx = mlx_init();
	void *mlx_window = mlx_new_window(mlx, width, height, "Image");
	
	sphere.pos.x = 250.0;
	sphere.pos.y = 250.0;
	sphere.pos.z = 20.0;
	sphere.r = 50.0;

	for(size_t i = 0; i < height; i++) {
		for(size_t j = 0; j < width; j++) {
			framebuffer[i][j] = malloc(sizeof(vect3f));
			if (sqrt(pow(i - sphere.pos.x,2) +pow(j - sphere.pos.y,2)) < sphere.r)
				mlx_pixel_put(mlx, mlx_window, i, j, 0x6CF42B);
			else
				mlx_pixel_put(mlx, mlx_window, i, j, 0xE2FFB2);
        }
    }
	mlx_loop(mlx);
}

