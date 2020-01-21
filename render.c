/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:20:04 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 16:20:21 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*render(t_list *listobj, t_list *listlight, const int width, const int height)
{
	vect3f			**framebuffer;
	size_t			i[2];
	void			*mlx[2];
	const float		fov = M_PI/3;
	float			vue[3];
	int				antiA = 4;
	vect3f			fcolor;
	float			a;
	float			b;
	int				c;
	vect3f			origin = c_vect3f(0, 0, 0);

	framebuffer = malloc(sizeof(vect3f *) * width);
	mlx[0] = mlx_init();
	mlx[1] = mlx_new_window(mlx[0], width, height, "Image");
	i[0] = 0;
	while (i[0] < width)
	{
		//if (i[0] > width / 2)
		//	origin = c_vect3f(-3.6, 0, 0);
		framebuffer[i[0]] = malloc(sizeof(vect3f) * height);
		i[1] = 0;
		while (i[1] < height)
		{
			float pitch = 2 * M_PI;
			float yaw = 0;
			vue[0] = (i[0] + 0.5) - width / 2;
			vue[1] = -(i[1] + 0.5) + height / 2 ;
			vue[2] = -height/(2.*tan(fov/2.));
			framebuffer[i[0]][i[1]] = cast_ray(origin, normalize(c_vect3f(vue[0] * cos(pitch) + vue[2] * sin(pitch), vue[1] , vue[2] * cos(pitch) - vue[0] * sin(pitch))), listobj, listlight, 0);
			fcolor = framebuffer[i[0]][i[1]];
			b = 1 / (float)antiA;
			c = 1;
			while (b < 1 - 1/ antiA)
			{
				a = 1 / (float)antiA;
				while (a < 1 - 1/ antiA)
				{	
					vue[0] = (i[0] + a) - width / 2;
					vue[1] = -(i[1] + b) + height / 2 ;
					vue[2] = -height/(2.*tan(fov/2.));
					framebuffer[i[0]][i[1]] = cast_ray(origin, normalize(c_vect3f(vue[0] * cos(pitch) + vue[2] * sin(pitch), vue[1] , vue[2] * cos(pitch) - vue[0] * sin(pitch))), listobj, listlight, 0);
					fcolor = v_plus(fcolor, framebuffer[i[0]][i[1]]);
					a += 2 / (float)antiA;
					c++;
				}
			b += 2 / (float)antiA;
			}
			fcolor = v_div(fcolor, c);
			mlx_pixel_put(mlx[0], mlx[1], i[0], i[1], c_color(fcolor));
			i[1]++;
		}
		free(framebuffer[i[0]]);
		i[0]++;
	}
	return (mlx[0]);
}