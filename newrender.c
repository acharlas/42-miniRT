/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newrender.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:20:04 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/03 15:41:26 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void	render(t_list *listobj, t_list *listlight, void *mlx_ptr, void *mlx_win)
{
	unsigned int	*framebuffer;
	void			*framebuffer_pre;
	void			*mlx[2];
	const float		fov = M_PI/3;
	float			*vue;
	int x, y;
	int bits, size, end;

    vue = malloc(sizeof(float) * 3);
	framebuffer_pre = mlx_new_image(mlx_ptr, Width, Height);
	framebuffer = (unsigned int *)mlx_get_data_addr(framebuffer_pre, &bits, &size, &end);
	x = 0;
	while (x < Width)
	{
		y = 0;
		while (y < Height)
		{
			vue[0] = (x + 0.5) - Width / 2;
			vue[1] = -(y + 0.5) + Height / 2;
			vue[2] = -Height/(2. * tan(fov/2.)); //TODO fov = parametre dans le .rt
			t_ray ray = {c_vect3f(0, 0, 0), normalize(c_vect3f(vue[0], vue[1], vue[2])), 0.};
			framebuffer[y + x * size / 4] = c_color(verif_color(cast_ray(ray, listobj, listlight)));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx_ptr, mlx_win, framebuffer, 0, 0);
	//mlx_destroy_image(void *mlx_ptr, void *img_ptr)
}
