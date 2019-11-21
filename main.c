/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/21 15:26:00 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "miniRT.h"
#include <float.h>

vect3f	ft_fill(float a, float b, float c)
{
	vect3f out;
	
	out.x = a;
	out.y = b;
	out.z = c;
	return (out);
}

int	ray_intersect(const vect3f orig, const vect3f dir, float t0, t_sphere sphere)
{
	vect3f L = ft_fill(sphere.pos.x - orig.x, sphere.pos.y - orig.y, sphere.pos.z - orig.z);
    float tca = L.x * dir.x + L.y * dir.y + L.z * dir.z;
    float d2 = (L.x * L.x + L.y * L.y + L.z * L.z) - (tca*tca);
    if (d2 > sphere.r*sphere.r)
		return 0;
    float thc = sqrtf(sphere.r*sphere.r - d2);
    t0       = tca - thc;
    float t1 = tca + thc;
    if (t0 < 0) 
		t0 = t1;
    if (t0 < 0) 
		return 0;
    return 1;
}

vect3f	normalize(vect3f this)
{
	vect3f out;
	out.x = this.x / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.y = this.y / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.z = this.z / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	return (out);
}

vect3f cast_ray(vect3f orig, vect3f dir, t_sphere sphere)
{
	float sphere_dist = FLT_MAX;
	if (!ray_intersect(orig, dir, sphere_dist, sphere)) {
        return ft_fill(0.2, 0.7, 0.8); 
    }
	return ft_fill(0.4, 0.4, 0.3);
}

int main(void)
{
	const int width = 500;
	const int height = 500;
	const float	fov	= M_PI / 2;
	t_sphere sphere;
	vect3f framebuffer[width][height];

	void *mlx = mlx_init();
	void *mlx_window = mlx_new_window(mlx, width, height, "Image");
	
	sphere.pos.x = -3.0;
	sphere.pos.y = 0.0;
	sphere.pos.z = -16.0;
	sphere.r = 2.0;
	vect3f orig = ft_fill(0,0,0);
	for(size_t i = 0; i < height; i++) {
		for(size_t j = 0; j < width; j++) {
			float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
			float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
			vect3f dir = normalize(ft_fill(x, y, -1));
			framebuffer[i][j] = cast_ray(orig, dir, sphere);
        }
    }
	for(size_t i = 0; i < height; i++) {
		for(size_t j = 0; j < width; j++) {
			int color = (int)(255 * framebuffer[i][j].x) << 16 | (int)(255 * framebuffer[i][j].y) << 8 | (int)(255 * framebuffer[i][j].z);
			mlx_pixel_put(mlx, mlx_window, i, j, color);
        }
    }
	mlx_loop(mlx);
}

// distance = sqrt(pow(i - sphere.pos.x,2) +pow(j - sphere.pos.y,2)) < sphere.r