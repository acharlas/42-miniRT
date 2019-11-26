/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/26 19:13:22 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool		ray_intersect(const vect3f *orig, const vect3f *dir, float *t0, const t_sphere sphere)
{
	vect3f	l;
	float	tca;
	float	d2;
	float	thc;
	float	t1;

	l = v_minus(sphere.pos, *orig);
	tca = v_dot(l, *dir);
	d2 = v_dot(l, l) - (tca * tca);
	if (d2 > powf(sphere.r, 2))
		return (0);
	thc = sqrtf(powf(sphere.r, 2) - d2);
	*t0 = tca - thc;
	t1 = tca + thc;
	if (*t0 < 0)
		*t0 = t1;
	if (*t0 < 0)
		return (0);
	return (1);
}

vect3f reflect(const vect3f *I, const vect3f *N)
{
	vect3f out;
	out = v_minus(*I, v_mult(*N, (2.f * v_dot(*I, *N))));
    return (out);
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
	float	dist_i;
	float checkboard_dist = FLT_MAX;
	while (listobj)
	{
		if (ray_intersect(orig, dir, &dist_i, *((t_sphere *)(listobj->data))) && dist_i < spheres_dist)
		{
			spheres_dist = dist_i;
			*hit = v_plus(*orig, v_mult(*dir, dist_i));
			*n = normalize(v_minus(*hit, ((t_sphere *)(listobj->data))->pos));
			*material = ((t_sphere *)(listobj->data))->material;
		}
		listobj = listobj->next;
	}
	if (ft_fabs(dir->y) > 0.001)
	{
		float d = -(orig->y + 4)/ dir->y; //equation y = -4;
		vect3f pt = v_plus(*orig,v_mult(*dir,d));
		if(d > 0 && ft_fabs(pt.x)<10 && pt.z<-10 && pt.z>-30 && d<spheres_dist)
		{
			checkboard_dist = d;
			*hit = pt;
			*n = c_vect3f(0,1,0);
			material->color = ((int)(.5*hit->x+1000) + (int)(.5*hit->z)) & 1 ? c_vect3f(0.3,0.3,0.3) : c_vect3f(0.3,0.2, 0.1);
			material->albedo.i = 0.8;
			material->albedo.j = 0.25;
			material->albedo.k = 0.0;
			material->albedo.l = 0.0;
			material->refractive_index = 1;
			material->specular_expo = 50;
		}
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

		vect3f shadow_origi = v_dot(light_dir, n) < 0 ? v_minus(point, v_mult(n, 0.001)) : v_plus(point, v_mult(n, 0.001));
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
		diffuse_light_intensity += ((t_light *)(listlight->data))->intensity * maxf(0.f, v_dot(light_dir, n));
		specular_light_intensity += powf(maxf(0.f, v_dot(reflect(&light_dir, &n), dir)), material.specular_expo) * ((t_light *)(listlight->data))->intensity; // 50. = specular_light_exposant
		listlight = listlight->next;
	}
	color = v_multv(v_plus(v_plus(v_plus(v_mult(material.color, (diffuse_light_intensity * material.albedo.i)), v_mult(add_color,(specular_light_intensity * material.albedo.j))),v_mult(reflect_color,material.albedo.k)),v_mult(refract_color, material.albedo.l)), add_color);
	color = verif_color(color);
	return (color); // color sphere
}

void	*render(t_list *listobj, t_list *listlight, const int width, const int height)
{
	vect3f			*framebuffer[width];
	size_t			i[2];
	void			*mlx[2];
	const float		fov = M_PI / 3.; // int donc = 1 mais bientot float
	float			vue[2];

	mlx[0] = mlx_init();
	mlx[1] = mlx_new_window(mlx[0], width, height, "Image");
	i[0] = 0;
	while (i[0] < width)
	{
		framebuffer[i[0]] = malloc(sizeof(vect3f) * height);
		i[1] = 0;
		while (i[1] < height)
		{
			vue[0] = (2 * (i[0] + 0.5) / width - 1) * tan(fov / 2) * width / height;
			vue[1] = -(2 * (i[1] + 0.5) / height - 1) * tan(fov / 2);
			mlx_pixel_put(mlx[0], mlx[1], i[0], i[1], c_color(framebuffer[i[0]][i[1]] = cast_ray(c_vect3f(0, 0, 0), normalize(c_vect3f(vue[0], vue[1], -1)), listobj, listlight, 0)));
			i[1]++;
		}
		free(framebuffer[i[0]]);
		i[0]++;
	}
	return (mlx[0]);
}

int		main(void)
{
	const int width = 1024;
	const int height = 768;
	void *mlx;
	t_list *spheres = NULL;
	t_list *listlight = NULL;
	
	t_material ivoire = c_material(c_vect3f(0.4, 0.4, 0.3), c_vect4f(0.6, 0.3, 0.1, 0), 1.0, 50.);
	t_material redrubber = c_material(c_vect3f(0.3, 0.1, 0.1), c_vect4f(0.9, 0.1, 0.0, 0), 1.0, 10.);
	t_material glass = c_material(c_vect3f(0.6, 0.7, 0.8), c_vect4f(0, 0.5, 0.1, 0.8), 1.5, 125.);
	t_material mirroir = c_material(c_vect3f(1, 1, 1), c_vect4f(0, 10.0, 0.8, 0), 1.0, 1425.);

	c_sphere(&spheres, c_vect3f(-3, 0, -16), ivoire, 2);
	c_sphere(&spheres, c_vect3f(-1, -1.5, -12), glass, 2);
	c_sphere(&spheres, c_vect3f(1.5, -0.5, -18), redrubber, 3);
	c_sphere(&spheres, c_vect3f(7, 5, -18), mirroir, 4);

	c_light(&listlight, c_vect3f(-20, 20, 20), c_vect3f(1, 1, 1), 1.5);
	c_light(&listlight, c_vect3f(30, 50, -25), c_vect3f(1, 1, 1), 1.8);
	c_light(&listlight, c_vect3f(30, 20, 30), c_vect3f(1, 1, 1), 1.7);

	mlx = render(spheres, listlight, width, height);
	mlx_loop(mlx);
}
