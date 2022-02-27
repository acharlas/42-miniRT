/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:16 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:17 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline simd_float3		get_vue(int x, int y, t_scene *scene,\
		t_camera *eye)
{
	simd_float3	vue;

	vue = simd_make_float3((float)((x + 0.5f) - scene->width / 2.f),
			(float)(-(y + 0.5f) + scene->height / 2.f),
			(float)(-scene->height / (2 * tan(eye->fov / 2.f))));
	return (simd_normalize(vue));
}

static inline t_frame			*setup_frame(t_scene *scene)
{
	t_frame		*frame;

	frame = p_malloc(sizeof(t_frame), 1, "frame");
	frame->eye = scene->listcam->content;
	frame->ray.orig = frame->eye->orig;
	frame->ptr = mlx_new_image(scene->mlx_ptr, scene->width, scene->height);
	frame->buffer = (unsigned int *)mlx_get_data_addr(frame->ptr, \
			&frame->info[0], &frame->info[1], &frame->info[2]);
	return (frame);
}

static void						process_image(t_scene *sc, t_frame *fr)
{
	if (sc->rend == SAVETOFILE)
		mlx_image_to_bmp(fr->buffer, fr->info[1], sc->width, sc->height);
	else
		mlx_put_image_to_window(sc->mlx_ptr, sc->win_ptr, fr->ptr, 0, 0);
	mlx_destroy_image(sc->mlx_ptr, fr->ptr);
}

int								render(t_scene *sc)
{
	t_frame		*fr;
	int			x;
	int			y;

	if (sc->rend == NOCHANGE)
		return (0);
	fr = setup_frame(sc);
	x = -1;
	while (++x < sc->width)
	{
		y = 0;
		while (y < sc->height)
		{
			fr->vue = get_vue(x, y, sc, fr->eye);
			fr->ray.dir = simd_mul(align_with(fr->eye->orient), fr->vue);
			fr->buffer[x + y++ * fr->info[1] / 4] = color_to_int(\
					cast_ray(fr->ray, sc->listobj, sc->listlight, sc));
		}
	}
	process_image(sc, fr);
	p_free(fr);
	sc->rend = NOCHANGE;
	return (0);
}
