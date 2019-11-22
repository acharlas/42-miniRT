/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/22 10:10:06 by acharlas         ###   ########.fr       */
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

int	ft_lstsize(t_listobj *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


// int scene_intersect(vect3f orig, vect3f dir, )

int	ray_intersect(const vect3f orig, const vect3f dir, float t0, t_listobj *listobj)
{
	//vect3f L = ft_fill(sphere.pos.x - orig.x, sphere.pos.y - orig.y, sphere.pos.z - orig.z);
}

vect3f	normalize(vect3f this)
{
	vect3f out;
	out.x = this.x / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.y = this.y / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.z = this.z / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	return (out);
}

vect3f cast_ray(vect3f orig, vect3f dir, t_listobj *listobj)
{
		float sphere_dist = FLT_MAX;
		if (!ray_intersect(orig, dir, sphere_dist, listobj))
		{
			return (ft_fill(0.2, 0.7, 0.8));
		}
		return (listobj->data.sphere->color);
}

void render(t_listobj *listobj, const int width, const int height, void *mlx, void *mlx_window)
{
	
	const float	fov	= M_PI / 2;
	vect3f framebuffer[width][height];
	vect3f orig = ft_fill(0,0,0);

	for(size_t i = 0; i < width; i++)
	{
		for(size_t j = 0; j < height; j++)
		{
			float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
			float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
			vect3f dir = normalize(ft_fill(x, y, -1));
			framebuffer[i][j] = cast_ray(orig, dir, listobj);
        }
    }
	for(size_t i = 0; i < width; i++)
	{
		for(size_t j = 0; j < height; j++)
		{
			int color = (int)(255 * framebuffer[i][j].x) << 16 | (int)(255 * framebuffer[i][j].y) << 8 | (int)(255 * framebuffer[i][j].z);
			mlx_pixel_put(mlx, mlx_window, i, j, color);
        }
    }
	
}

t_listobj	*ft_lstnew(void *content)
{
	t_listobj	*list;

	if (!(list = malloc(sizeof(t_listobj))))
		return (NULL);
	list->data = content;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_front(t_listobj **alst, t_listobj *new)
{
	if (!alst)
		return ;
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}

int main(void)
{
	const int width = 1000;
	const int height = 600;
	t_listobj *listobj;
	
	t_sphere *sphere;
	sphere->pos.x = -3;
	sphere->pos.y = 0;
	sphere->pos.z = -16;
	sphere->r = 2;
	sphere->color.x = 1.0;
	sphere->color.y = 0.0;
	sphere->color.z = 0.0;

	t_sphere *sphere2;
	sphere2->pos.x = -20;
	sphere2->pos.y = 0;
	sphere2->pos.z = -50;
	sphere2->r = 2;
	sphere2->color.x = 0.8;
	sphere2->color.y = 1.0;
	sphere2->color.z = 0.0;
	ft_lstadd_front(&listobj, ft_lstnew(sphere));
	ft_lstadd_front(&listobj, ft_lstnew(sphere2));
	void *mlx = mlx_init();
	void *mlx_window = mlx_new_window(mlx, width, height, "Image");
	render(listobj, width, height, mlx, mlx_window);
	mlx_loop(mlx);
}
