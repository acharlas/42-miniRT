/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/23 11:23:36 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ray_intersect(const vect3f orig, const vect3f dir, float *t0, t_listobj *listobj)
{
	vect3f	l;
	float	tca;
	float	d2;
	float	thc;
	float	t1;

	l = v_minus(((t_sphere *)(listobj->data))->pos, orig);
	tca = v_dot(l, dir);
	d2 = v_dot(l, l) - (tca * tca);
	if (d2 > pow(((t_sphere *)(listobj->data))->r, 2))
		return (0);
	thc = sqrtf(pow(((t_sphere *)(listobj->data))->r, 2) - d2);
	*t0 = tca - thc;
	t1 = tca + thc;
	if (*t0 < 0)
		*t0 = t1;
	if (t0 < 0)
		return (0);
	return (1);
}

int		scene_intersect(vect3f orig, vect3f dir, t_listobj *listobj, vect3f *hit, vect3f *n, vect3f *color)
{
	float	spheres_dist = FLT_MAX;
	float	dist_i;

	while (listobj)
	{
		if (ray_intersect(orig, dir, &dist_i, listobj) && dist_i < spheres_dist)
		{
			*color = ((t_sphere *)(listobj->data))->color;
			spheres_dist = dist_i;
			*hit = v_plus(orig, v_mult(dir, dist_i));
			*n = normalize(v_minus(*hit, ((t_sphere *)(listobj->data))->pos));
		}
		listobj = listobj->next;
	}
	return (spheres_dist < 1000);
}

vect3f	cast_ray(vect3f orig, vect3f dir, t_listobj *listobj, t_listobj *listlight)
{
	float	sphere_dist = FLT_MAX;
	float	diffuse_light_intensity;
	float	specular_light_intensity;
	vect3f	color;
	vect3f	point;
	vect3f	n;
	vect3f	light_dir;
	
	if (!scene_intersect(orig, dir, listobj, &point, &n, &color))
		return (c_vect3f(0.57, 0, 0.25));
	diffuse_light_intensity = 0;
	specular_light_intensity = 0;
	while (listlight)
	{
		light_dir = normalize(v_minus(((t_light *)(listlight->data))->pos, point));
		diffuse_light_intensity += ((t_light *)(listlight->data))->intensity * maxf(0, v_dot(light_dir, n));
		listlight = listlight->next;
	}
	color = v_mult(color, diffuse_light_intensity);
	return (color);
}

void	render(t_listobj *listobj, t_listobj *listlight, const int width, const int height, void *mlx, void *mlx_window)
{
	const float		fov = M_PI / 2;
	const vect3f	orig = c_vect3f(0, 0, 0);
	float			vue[2];
	vect3f			dir;
	vect3f			*framebuffer[height];
	int				color;
	
	for (size_t i = 0 ; i < height; i++)
		framebuffer[i] = malloc(sizeof(vect3f) * width);
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			vue[0] =  (2 * (i + 0.5) / (float)width  - 1) * tan(fov / 2.) * width / (float)height;
			vue[1] = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
			dir = normalize(c_vect3f(vue[0], vue[1], -1));
			framebuffer[i][j] = cast_ray(orig, dir, listobj, listlight);
        }
    }
	for(size_t i = 0; i < width; i++)
	{
		for(size_t j = 0; j < height; j++)
		{
			color = c_color(framebuffer[i][j]); 
			mlx_pixel_put(mlx, mlx_window, i, j, color);
        }
		free(framebuffer[i]);
    }
}

int		main(void)
{
	const int width = 1000;
	const int height = 1000;
	t_listobj *listobj = NULL;
	t_listobj *listlight = NULL;
	
	t_sphere *sphere;
	t_sphere *sphere2;
	t_sphere *sphere3;
	sphere = malloc(sizeof(t_sphere));
	sphere->pos = c_vect3f(-6, 0, -16);
	sphere->r = 4;
	sphere->color = c_vect3f(0.87, 0.70, 1);
	
	ft_lstadd_front(&listobj, ft_lstnew(sphere));
	sphere2 = malloc(sizeof(t_sphere));
	sphere2->pos = c_vect3f(-1.0, 0, -12);
	sphere2->r = 4;
	sphere2->color = c_vect3f(0.486, 0.27, 0.65);
	ft_lstadd_front(&listobj, ft_lstnew(sphere2));
	sphere3 = malloc(sizeof(t_sphere));
	sphere3->pos = c_vect3f(1.5, -0.5, -18);
	sphere3->r = 6;
	sphere3->color = c_vect3f(0.27, 0.08, 0.431);
	ft_lstadd_front(&listobj, ft_lstnew(sphere3));
	t_light *light;
	light = malloc(sizeof(t_light));
	light->pos = c_vect3f(20, 20, 20);
	light->intensity = 1.0;
	ft_lstadd_front(&listlight, ft_lstnew(light));
	void *mlx = mlx_init();
	void *mlx_window = mlx_new_window(mlx, width, height, "Image");
	render(listobj, listlight, width, height, mlx, mlx_window);
	mlx_loop(mlx);
}