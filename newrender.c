/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newrender.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:20:04 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/07 11:35:16 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


int	render(t_list *listobj, t_list *listlight, void *mlx_ptr, void *mlx_win)
{
	unsigned int	*framebuffer;
	void			*framebuffer_pre;
	const float		fov = M_PI/3;
	int x, y;
	int bits, size, end;
	__m128	color;
	__m128	vue;

	framebuffer_pre = mlx_new_image(mlx_ptr, Width, Height);
	framebuffer = (unsigned int *)mlx_get_data_addr(framebuffer_pre, &bits, &size, &end);
	x = 0;
	while (x < Width)
	{
		y = 0;
		while (y < Height)
		{
			vue = _mm_setr_ps((x + 0.5) - Width / 2, - (y + 0.5) + Height / 2, - Height / (2. * tan(fov / 2.)), 0.);
			t_ray ray = {_mm_setr_ps(0, 0, 0, 0), normalize(vue)};
			color = antiAliasing(3, cast_ray(ray, listobj, listlight, 0), x, y, fov, listobj, listlight);
			framebuffer[x + y * size / 4] = color_to_int(color);
			//mlx_pixel_put(mlx_ptr, mlx_win, x, y, color);
			y++;
			//printf("x %d - y %d", x, y);

		}
		x++;
	}
	mlx_put_image_to_window(mlx_ptr, mlx_win, framebuffer_pre, 0, 0);
	return (0);
	//mlx_destroy_image(void *mlx_ptr, void *img_ptr)
}
