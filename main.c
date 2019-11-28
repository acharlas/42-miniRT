/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/28 23:56:36 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


vect3f reflect(const vect3f *I, const vect3f *N)
{
    return (v_minus(*I, v_mult(*N, (2.f * v_dot(*I, *N)))));
}

vect3f	refract(const vect3f *I, const vect3f *n, const float eta_t, const float eta_i)
{
	float cosi = -maxf(-1., minf(1., v_dot(*I, *n)));
	if (cosi < 0)
	{
		vect3f m = v_minus(c_vect3f(0,0,0), *n);
		return (refract(I, &m, eta_i, eta_t));
	}
	float eta = (eta_i / eta_t);
	float k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? c_vect3f(1,0,0) : v_plus(v_mult(*I,eta), v_mult(*n,eta*cosi -sqrtf(k)));
}

int		scene_intersect(const vect3f *orig, const vect3f *dir, const t_list *listobj, vect3f *hit, vect3f *n, t_material *material)
{
	float	spheres_dist = FLT_MAX;
	float checkboard_dist = FLT_MAX;
	float d;
	float	dist_i = 0;
	
	while (listobj)
	{
		if(listobj->name == 's')
		{
			if (SPHERE->ray_intersect(orig, dir, &dist_i, *SPHERE) && dist_i < spheres_dist)
			{
				spheres_dist = dist_i;
				// d = minf(spheres_dist, d);
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize(v_minus(*hit, SPHERE->pos));
				*material = SPHERE->material;
			}
		}
		else if(listobj->name == 'p')
		{
			if(SQUARE->ray_intersect(orig, dir, &dist_i, *SQUARE))
			{
				checkboard_dist = dist_i;
				// d = minf(checkboard_dist, d);
				*hit = v_plus(*orig, v_mult(*dir,dist_i));
				*n = normalize(v_minus(*hit, SQUARE->pos));
				*material = SQUARE->material;
			}
		}
		listobj = listobj->next;
	}
	return (minf(spheres_dist, checkboard_dist) < 1000);
}

vect3f	cast_ray(const vect3f orig, const vect3f dir, const t_list *listobj, const t_list *listlight, size_t depth)
{
	float	diffuse_light_intensity;
	float	specular_light_intensity;
	vect3f color;
	t_material	material;
	vect3f	point;
	vect3f	n;
	vect3f	light_dir;
	vect3f reflect_dir;
	vect3f reflect_orig;
	vect3f reflect_color;
	vect3f refract_dir;
	vect3f refract_orig;
	vect3f refract_color;
	vect3f add_color = c_vect3f(0, 0, 0);
	
	if (depth > 4 || !scene_intersect(&orig, &dir, listobj, &point, &n, &material))
		return (bg_color(126,192,238)); //color background
	
	refract_dir = normalize(refract(&dir, &n, material.refractive_index, 1.0));
	refract_orig = v_dot(refract_dir, n) < 0 ? v_minus(point, v_mult(n, 0.001)) : v_plus(point, v_mult(n, 0.001));
	refract_color = cast_ray(refract_orig, refract_dir, listobj, listlight, depth + 1);
	reflect_dir = normalize(reflect(&dir, &n));
	reflect_orig = v_dot(reflect_dir, n) < 0 ? v_minus(point, v_mult(n, 0.001)) : v_plus(point, v_mult(n, 0.001));
	reflect_color = cast_ray(reflect_orig, reflect_dir, listobj, listlight, (depth + 1));
	diffuse_light_intensity = 0;
	specular_light_intensity = 0;
	while (listlight)
	{
		light_dir = normalize(v_minus(((t_light *)(listlight->data))->pos, point));
		float light_distance = norm(v_minus(((t_light *)(listlight->data))->pos, point));
		float lightdot = v_dot(light_dir, n);

		vect3f shadow_origi = lightdot < 0 ? v_minus(point, v_mult(n, 0.001)) : v_plus(point, v_mult(n, 0.001));
		vect3f shadow_pt = c_vect3f(0, 0, 0);
		vect3f shadow_N = c_vect3f(0, 0, 0);
		t_material tmpmaterial;
		add_color = v_plus(add_color, v_div(((t_light *)(listlight->data))->color, ft_lstsize(listlight)));
		add_color = verif_color(add_color);
		if (scene_intersect(&shadow_origi, &light_dir, listobj, &shadow_pt, &shadow_N, &tmpmaterial) && (norm(v_minus(shadow_pt, shadow_origi))) < light_distance)
		{
			listlight = listlight->next;
		 	continue;
		}
		diffuse_light_intensity += ((t_light *)(listlight->data))->intensity * maxf(0.f, lightdot); 
		specular_light_intensity += powf(maxf(0.f, v_dot(reflect(&light_dir, &n), dir)), material.specular_expo) * ((t_light *)(listlight->data))->intensity; // 50. = specular_light_exposant
		listlight = listlight->next;
	}
	color = v_multv(v_plus(v_plus(v_plus(v_mult(material.color, (diffuse_light_intensity * material.albedo.i)), v_mult(add_color,(specular_light_intensity * material.albedo.j))),v_mult(reflect_color,material.albedo.k)),v_mult(refract_color, material.albedo.l)), add_color);
	color = verif_color(color);
	return (color); // color sphere
}

void	*render(t_list *listobj, t_list *listlight, const int width, const int height)
{
	vect3f			**framebuffer;
	size_t			i[2];
	void			*mlx[2];
	const float		fov = M_PI / 3.;
	vect3f			orig = {0, 0, 0};
	float			tanfov = tan(fov / 2);

	framebuffer = malloc(sizeof(vect3f *) * width);
	mlx[0] = mlx_init();
	mlx[1] = mlx_new_window(mlx[0], width, height, "Image");
	i[0] = 0;
	while (i[0] < width)
	{
		framebuffer[i[0]] = malloc(sizeof(vect3f) * height);
		i[1] = 0;
		while (i[1] < height)
		{
			float pitch = M_PI;
			float yaw =  0;
			vect3f vue = {((2 * (i[0] + 0.5) / width - 1) * tanfov * width / height), -(2 * (i[1] + 0.5) / height - 1) * tanfov, -1};
			mlx_pixel_put(mlx[0], mlx[1], i[0], i[1], c_color(framebuffer[i[0]][i[1]] = cast_ray(orig, normalize(vue), listobj, listlight, 0)));
			i[1]++;
		}
		free(framebuffer[i[0]]);
		i[0]++;
	}
	free(framebuffer);
	return (mlx[0]);
}

int		main(void)
{
	const int width = 500;
	const int height = 500;
	void *mlx;
	t_list *objet = NULL;
	t_list *listlight = NULL;
	t_square *square;
	t_square *square2;
	
	t_material ivoire = c_material(c_vect3f(0.4, 0.4, 0.3), c_vect4f(0.6, 0.3, 0.1, 0), 1.0, 50.);
	t_material redrubber = c_material(c_vect3f(0.3, 0.1, 0.1), c_vect4f(0.9, 0.1, 0.0, 0), 1.0, 10.);
	t_material glass = c_material(c_vect3f(0.6, 0.7, 0.8), c_vect4f(0, 0.5, 0.1, 0.8), 1.5, 125.);
	t_material mirroir = c_material(c_vect3f(1, 1, 1), c_vect4f(0, 10.0, 0.8, 0), 1.0, 1425.);
	t_material plane = c_material(c_vect3f(0.9, 0.3, 0.3), c_vect4f(10, 0.3, 0.1, 0), 1.0, 125.);

	square = malloc(sizeof(t_square));
	square->pos = c_vect3f(0, -4, 0);
	square->taille.a = 10;
	square->taille.b = 5;
	square->material = ivoire;
	square->ray_intersect = ray_intersect_square;

	square2 = malloc(sizeof(t_square));
	square2->pos = c_vect3f(0, -1.5, 0);
	square2->taille.a = 5;
	square2->taille.b = 5;
	square2->material = ivoire;
	square2->ray_intersect = ray_intersect_square;

	c_sphere(&objet, c_vect3f(-1, -1.5, -12), glass, 2, ray_intersect_sphere);
	c_sphere(&objet, c_vect3f(1.5, -0.5, -18), redrubber, 3,ray_intersect_sphere);
	c_sphere(&objet, c_vect3f(-3, 0, -16), ivoire, 2, ray_intersect_sphere);
	c_sphere(&objet, c_vect3f(7, 5, -18), mirroir, 4, ray_intersect_sphere);
	ft_lstadd_front(&objet, ft_lstnew(square, 'p'));
	ft_lstadd_front(&objet, ft_lstnew(square2, 'p'));
	



	c_light(&listlight, c_vect3f(-20, 20, 20), c_vect3f(1, 1, 1), 1.5);
	c_light(&listlight, c_vect3f(30, 50, -25), c_vect3f(1, 1, 1), 1.8);
	c_light(&listlight, c_vect3f(30, 20, 30), c_vect3f(1, 1, 1), 1.7);

	mlx = render(objet, listlight, width, height);
	//mlx_loop(mlx);
}
