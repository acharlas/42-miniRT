/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/22 17:14:52 by acharlas         ###   ########.fr       */
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

vect3f	normalize(vect3f this)
{
	vect3f out;
	out.x = this.x / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.y = this.y / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	out.z = this.z / sqrt(pow(this.x,2) + pow(this.y,2) + pow(this.z,2));
	return (out);
}

int	ray_intersect(const vect3f orig, const vect3f dir, float *t0, t_listobj *listobj)
{
	vect3f L = ft_fill(((t_sphere *)(listobj->data))->pos.x - orig.x, ((t_sphere *)(listobj->data))->pos.y - orig.y, ((t_sphere *)(listobj->data))->pos.z - orig.z);
	float tca = L.x * dir.x + L.y * dir.y + L.z * dir.z;
    float d2 = (L.x * L.x + L.y * L.y + L.z * L.z) - (tca*tca);
    if (d2 > ((t_sphere *)(listobj->data))->r*((t_sphere *)(listobj->data))->r)
		return 0;
    float thc = sqrtf(((t_sphere *)(listobj->data))->r*((t_sphere *)(listobj->data))->r - d2);
    *t0       = tca - thc;
    float t1 = tca + thc;
    if (*t0 < 0) 
		*t0 = t1;
    if (t0 < 0) 
		return 0;
    return 1;

}

int scene_intersect(vect3f orig, vect3f dir, t_listobj *listobj, vect3f *color)
{
	float spheres_dist = FLT_MAX;
	while(listobj)
	{
		float dist_i;
		if(ray_intersect(orig, dir, &dist_i, listobj) && dist_i < spheres_dist)
		{
				*color = ((t_sphere *)(listobj->data))->color;
				spheres_dist = dist_i;
		}
		listobj = listobj->next;
	}
	return (spheres_dist < 1000);
}

vect3f cast_ray(vect3f orig, vect3f dir, t_listobj *listobj)
{
		float sphere_dist = FLT_MAX;
		vect3f color;
		if (!scene_intersect(orig, dir, listobj, &color))
		{
			return (ft_fill(0.57, 0, 0.25));
		}
		return (color);
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

void ft_lstadd_front(t_listobj **alst, t_listobj *new)
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
	const int height = 1000;
	t_listobj *listobj = NULL;
	
	t_sphere *sphere;
	t_sphere *sphere2;
	t_sphere *sphere3;
	sphere = malloc(sizeof(t_sphere));
	sphere->pos = ft_fill(0, 0, -15);
	sphere->r = 2;
	sphere->color = ft_fill(0.87, 0.70, 1);
	
	ft_lstadd_front(&listobj, ft_lstnew(sphere));
	sphere2 = malloc(sizeof(t_sphere));
	sphere2->pos = ft_fill(10, 0, -25);
	sphere2->r = 2;
	sphere2->color = ft_fill(0.486, 0.27, 0.65);
	ft_lstadd_front(&listobj, ft_lstnew(sphere2));
	sphere3 = malloc(sizeof(t_sphere));
	sphere3->pos = ft_fill(20, 0, -35);
	sphere3->r = 2;
	sphere3->color = ft_fill(0.27, 0.08, 0.431);
	ft_lstadd_front(&listobj, ft_lstnew(sphere));
	void *mlx = mlx_init();
	void *mlx_window = mlx_new_window(mlx, width, height, "Image");
	render(listobj, width, height, mlx, mlx_window);
	mlx_loop(mlx);
}