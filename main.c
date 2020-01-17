/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/17 18:53:23 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


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
	float	dist_i;
	float	m;
	float	k;
	t_dist	t_dist;

	t_dist = init_dist();
	while (listobj)
	{
		if (ft_strncmp(listobj->name, "tr", 2) == 0)
		{
			if(TRIANGLE->ray_intersect(orig, dir, &dist_i, *TRIANGLE) && calcule_dist(dist_i, t_dist))
			{
				t_dist.tr_dist = dist_i;
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize(v_cross(v_minus(TRIANGLE->c1, TRIANGLE->c2),v_minus(TRIANGLE->c1, TRIANGLE->c3)));
				*material = TRIANGLE->material;
			}
		}
		else if (ft_strncmp(listobj->name, "cy", 2) == 0)
		{
			if(CYLINDER->ray_intersect(orig, dir, &dist_i, *CYLINDER) && calcule_dist(dist_i, t_dist))
			{
				t_dist.cy_dist = dist_i;
				m = v_dot(*dir, normalize(CYLINDER->rot)) * dist_i + v_dot(v_minus(*orig, CYLINDER->pos),normalize(CYLINDER->rot));
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize((v_minus(v_minus(*hit,CYLINDER->pos), v_mult(normalize(CYLINDER->rot), m))));
				*material = CYLINDER->material;
			}
		}
		else if(ft_strncmp(listobj->name, "pl", 2) == 0)
		{
			if(PLANE->ray_intersect(orig, dir, &dist_i, *PLANE) && calcule_dist(dist_i, t_dist))
			{
				t_dist.pl_dist = dist_i;
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize(PLANE->rot);
				*material = PLANE->material;
			}
		}
		else if(ft_strncmp(listobj->name, "sp", 2) == 0)
		{
			if (SPHERE->ray_intersect(orig, dir, &dist_i, *SPHERE) && calcule_dist(dist_i, t_dist))
			{
				t_dist.sp_dist = dist_i;
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				*n = normalize(v_minus(*hit, SPHERE->pos));
				*material = SPHERE->material;
			}
		}
		else if(ft_strncmp(listobj->name, "co", 2) == 0)
		{
			if (CONE->ray_intersect(orig, dir, &dist_i, *CONE) && calcule_dist(dist_i, t_dist))
			{
				t_dist.co_dist = dist_i;
				*hit = v_plus(*orig, v_mult(*dir, dist_i));
				k = tan(((CONE->a / 2) * M_PI) / 180);
				m = v_dot(*dir, normalize(CYLINDER->rot)) * dist_i + v_dot(v_minus(*orig, CYLINDER->pos),normalize(CYLINDER->rot));
				*n = normalize((v_minus(v_minus(*hit,CYLINDER->pos), v_mult(v_mult(normalize(CYLINDER->rot), m), 1+k*k))));
				*material = CONE->material;
			}
		}
		listobj = listobj->next;
	}
	return (minimumfloat(5 , t_dist.pl_dist, t_dist.sp_dist, t_dist.cy_dist, t_dist.co_dist, t_dist.tr_dist) < 1000);
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
		return (bg_color(130,231,255)); //color background
	
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
	return (color);
}

void	*render(t_list *listobj, t_list *listlight, const int width, const int height)
{
	vect3f			**framebuffer;
	size_t			i[2];
	void			*mlx[2];
	const float		fov = M_PI / 3.;
	float			vue[3];

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
			vue[2] = -1;
			vue[0] = ((2 * (i[0] + 0.5) / width - 1) * tan(fov / 2) * width / height);
			vue[1] = -(2 * (i[1] + 0.5) / height - 1) * tan(fov / 2);
			mlx_pixel_put(mlx[0], mlx[1], i[0], i[1], c_color(framebuffer[i[0]][i[1]] = cast_ray(c_vect3f(0, 0, 0), normalize(c_vect3f(vue[0], vue[1], vue[2])), listobj, listlight, 0)));
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
	char *line;
	char ***tab;
	char **array;
	t_list *objet = NULL;
	t_list *listlight = NULL;
	t_material ivoire = c_material(c_vect3f(0.4, 0.4, 0.3), c_vect4f(0.6, 0.3, 0.1, 0), 1.0, 50.);
	t_material redrubber = c_material(c_vect3f(1, 0.96, 0.0), c_vect4f(0.3, 0.0, 0.0, 0), 1.0, 10.);
	t_material glass = c_material(c_vect3f(0.6, 0.9, 0.8), c_vect4f(0, 0.5, 0.1, 0.8), 1.5, 125.);
	t_material mirroir = c_material(c_vect3f(1, 1, 1), c_vect4f(0, 10.0, 0.8, 0), 1.0, 1425.);
	t_material plane = c_material(c_vect3f(0.3, 0.2, 0.1), c_vect4f(0.8, 0.25, 0.0, 0.0), 1.0, 100.);
	t_material blackrubber = c_material(c_vect3f(0.01,0.01,0.01), c_vect4f(0.9,0.1,0.0,0), 1.0, 10);
	t_material fluo = c_material(c_vect3f(0.01,0.45,0.001), c_vect4f(0.9, 0.7,0.6,0), 1.0, 125.);
	

	// c_triangle(&objet, c_vect3f(5,-4,-10),c_vect3f(-5,-4,-10),c_vect3f(0,-4,-15), plane);
	// c_cylinder(&objet, c_vect3f(-5, 0,-15), c_vect3f(0,1,1), plane, 1, 5);
	// c_cone(&objet, c_vect3f(-10, 5, -30), c_vect3f(1, 1, 0), plane, 30);
	// c_plane(&objet, c_vect3f(0, -5, 0), c_vect3f(0, 1, 0), mirroir);
	// c_sphere(&objet, c_vect3f(-1, 2.6, -12), redrubber, 1.2);
	// c_sphere(&objet, c_vect3f(-3, 0, -16), ivoire, 2);
	// c_sphere(&objet, c_vect3f(3, 0, -15), glass, 3);
	// c_sphere(&objet, c_vect3f(3, 0, -15), blackrubber, 1);
	// c_sphere(&objet, c_vect3f(7, 5, -18), mirroir, 4);
	c_light(&listlight, c_vect3f(-20, 20, 20), c_vect3f(1, 1, 1), 1.5);
	c_light(&listlight, c_vect3f(30, 50, -25), c_vect3f(1, 1, 1), 1.8);
	c_light(&listlight, c_vect3f(30, 20, 30), c_vect3f(1, 1, 1), 1.7);
		c_light(&listlight, c_vect3f(0, 0, 0), c_vect3f(1, 1, 1), 2.1);
	
	int fd = open("Deer.obj", O_RDONLY);
	int i = 0;
	tab = malloc(sizeof(char ***) * 832);
	while(get_next_line(fd,&line) && i != 832)
	{
		tab[i] = ft_split(line, ' ');
		i++;
	}
	i = 0;
	float x = 0;
	float y = 0;
	float z = 10;
	float div = 100.;
	while (get_next_line(fd, &line))
	{
		array = ft_split(line, ' ');
		float a = atof(tab[atoi(array[1]) - 1][1]) / div;
		float b = atof(tab[atoi(array[1]) - 1][2]) / div;
		float c = atof(tab[atoi(array[1]) - 1][3]) / div;
		float d = atof(tab[atoi(array[2]) - 1][1]) / div;
		float e = atof(tab[atoi(array[2]) - 1][2]) / div;
		float f = atof(tab[atoi(array[2]) - 1][3]) / div;
		float g = atof(tab[atoi(array[3]) - 1][1]) / div;
		float h = atof(tab[atoi(array[3]) - 1][2]) / div;
		float i = atof(tab[atoi(array[3]) - 1][3]) / div;
		c_triangle(&objet, c_vect3f(a - x,  b - y,  c - z), c_vect3f(d - x, e - y, f - z), c_vect3f(g - x, h - y, i - z), plane);
	}
	free(tab);
	
	mlx = render(objet, listlight, width, height);
	mlx_loop(mlx);
}
