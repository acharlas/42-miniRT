/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newrender.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:20:04 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/07 14:07:52 by rdeban           ###   ########.fr       */
/*   Updated: 2020/02/07 11:47:20 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


int	render(t_par *par)
{
	unsigned int	*framebuffer;
	void			*framebuffer_pre;
	//const float		fov = M_PI/3;
	int x, y;
	int bits, size, end;
	__m128	color;
	__m128	vue;

	if (par->state != 2)
		return (1);
	framebuffer_pre = mlx_new_image(par->mlx_ptr, Width, Height);
	framebuffer = (unsigned int *)mlx_get_data_addr(framebuffer_pre, &bits, &size, &end);
	x = 0;
	//ProfilerStart("Perf_log");
	while (x < Width)
	{
		y = 0;
		while (y < Height)
		{
			vue = _mm_setr_ps((x + 0.5) - Width / 2, - (y + 0.5) + Height / 2, - Height / (2. * tan(FOV / 2.)), 0.);
			t_ray ray = {_mm_setr_ps(0, 1, 35, 0), normalize(vue)};
			color = antiAliasing(2, cast_ray(ray, par->listobj, par->listlight, 0), x, y, FOV, par->listobj, par->listlight);
			framebuffer[x + y * size / 4] = color_to_int(color);
			//mlx_pixel_put(mlx_ptr, mlx_win, x, y, color);
			y++;
			//printf("x %d - y %d", x, y);

		}
		x++;
	}
	//ProfilerStop();
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, framebuffer_pre, 0, 0);
	mlx_destroy_image(par->mlx_ptr, framebuffer_pre);
	par->state = 0;
	return (0);
}
