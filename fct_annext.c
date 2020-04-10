/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_annext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:19:13 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 15:40:52 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float maxf(float a, float b)
{
	if (a >= b)
		return (a);
	return(b);
}

float ft_fabs(float a)
{
	if(a < 0)
		return(-a);
	return(a);
}

float minf(float a, float b)
{
	if (a >= b)
		return (b);
	return(a);
}


unsigned int	color_to_int(__m128 v)
{
	float tmp[4];
	_mm_storeu_ps(tmp, v);
	unsigned int color;
	if (tmp[0] > 1)
		tmp[0] = 1;
	if (tmp[1] > 1)
		tmp[1] = 1;
	if (tmp[2] > 1)
		tmp[2] = 1;
	color = (int)(255 * tmp[0]) << 16;
	color |= (int)(255 * tmp[1]) << 8;
	color |= (int)(255 * tmp[2]);
	return (color);
}


#include "../includes/minirt.h"
#include <immintrin.h>
#include "../libft/libft.h"

double ms;
t_camera *eye;
char STATE = 0;

float	shortestDistanceToSurface(simd_float3 eye, simd_float3 marchingDirection, t_scene *scene);
simd_float3 estimateNormal(simd_float3 p, t_scene *s);

int deal_key(int key, void *param)
{
	//float out[4];
	STATE = 1;
	if (key == 13)
	{
		printf("Incrementing z by 1\n");
		eye->point += vector3(0.f, 0.f, 0.5f);
	}
	else if (key == 1)
	{
		printf("Decrementing z by 1\n");
		eye->point += vector3(0.f, 0.f, -0.5f);
	}
	else if (key == 0)
	{
		printf("Decrementing x by 1\n");
		eye->point += vector3(-0.5f, 0.f, 0.f);
	}
	else if (key == 2)
	{
		printf("Incrementing x by 1\n");
		eye->point += vector3(0.5f, 0.f, 0.f);
	}
	else if (key == 12)
	{
		printf("Decrementing y by 1\n");
		eye->point += vector3(0.f, -0.5f, 0.f);
	}
	else if (key == 14)
	{
		printf("Incrementing y by 1\n");
		eye->point += vector3(0.f, 0.5f, 0.f);
	}
	else
		return (1);
	printf("New eye->point value is {%f, %f, %f}\n", eye->point.x, eye->point.y, eye->point.z);
	return (0);
}

unsigned int	color_to_int(simd_float3 v)
{
	unsigned int color;
	if (v.x > 1)
		v.x = 1;
	if (v.y > 1)
		v.y = 1;
	if (v.z > 1)
		v.z = 1;
	color = (int)(255 * v.x) << 16;
	color |= (int)(255 * v.y) << 8;
	color |= (int)(255 * v.z);
	return (color);
}

static inline simd_float3 get_obj_col(t_obj *obj)
{
	return (obj->color);
}



float	sceneSDF_list(simd_float3 v, t_scene *s, int rays)
{
	t_list	*listobj;
	float	min;
	float	tmp;

	min = FLT_MAX;
	listobj = s->listobj;
	while (listobj)
	{
		if (listobj->content && ((tmp = general_sdf(v, listobj->content)) < min))
		{
			min = tmp;
			if(rays == 1)
			{
				s->material = get_obj_col(listobj->content);
				s->l_obj = (t_obj *)listobj->content;
			}
		}
		listobj = listobj->next;
	}
	return (min);
}

float softshadow(simd_float3 ro, simd_float3 rd, t_scene *s)
{
	float	res = 1.0f;
	float	ph = 1.0;
	float	y;
	float	d;
	for(float t = 0.1f; t < simd_length(rd);)
	{
		float h = sceneSDF_list(ro + simd_normalize(rd) * t, s, 0);
		if(h < EPSILON)
			return 0.0f;
		y = t == 0.1 ? 0.0 : h * h / (2.0f * ph);
		d = sqrtf(h * h - y * y);
		res = MIN(res, 50.f * d/ MAX(0.0f, t - y)); // 50.f = k
		ph = h;
		t += h;
	}
	return ft_clamp(res, 0.0f,1.0f);
}


simd_float3x3 viewMatrix(simd_float3 eye, simd_float3 center, simd_float3 up)
{
	const	simd_float3 f = simd_normalize(center - eye);
	const	simd_float3 s = simd_normalize(simd_cross(f, up));
	const	simd_float3 u = simd_cross(s, f);
	return (simd_matrix(s, u, -f));
}

float	shortestDistanceToSurface(simd_float3 eye, \
		simd_float3 marchingDirection, t_scene *scene)
{
	float depth;
	float dist;
	int i;

	depth = MIN_DIST;
	i = 0;
	while (i < MAX_MARCHING_STEPS)
	{
		dist = sceneSDF_list(eye + marchingDirection * depth, scene,1);
		if (dist < EPSILON)
			return depth;
		depth += dist;
		if (depth >= MAX_DIST)
			return MAX_DIST;
		i++;
	}
	if (depth <= MAX_DIST)
		return depth;
	return MAX_DIST;
}

bool has_normal(t_obj *obj)
{
	if (obj->id == PLANE ||
			obj->id == SQUARE)
		return true;
	return false;
}

simd_float3 get_normal(t_obj *obj)
{
	if (obj->id == PLANE)
		return (obj->type.plane->orientation);
	return (obj->type.square->orientation);
}

simd_float3 estimateNormal(simd_float3 p, t_scene *s)
{
	if (has_normal(s->l_obj))
		return (get_normal(s->l_obj));
	return (simd_normalize(vector3(\
					sceneSDF_list(vector3(p.x + EPSILON, p.y, p.z), s,0)\
					- sceneSDF_list(vector3(p.x - EPSILON, p.y, p.z), s,0),\
					sceneSDF_list(vector3(p.x, p.y + EPSILON, p.z), s,0)\
					- sceneSDF_list(vector3(p.x, p.y - EPSILON, p.z), s,0),
					sceneSDF_list(vector3(p.x, p.y, p.z + EPSILON), s,0)\
					- sceneSDF_list(vector3(p.x, p.y, p.z - EPSILON), s,0)\
					)));
}

t_camera *get_camera(t_obj *obj)
{
	t_camera *cam;
	cam = obj->type.camera;
	return (cam);
}

simd_float3 phongContribForLight(simd_float3 p, simd_float3 eye, t_obj *light, t_scene *scene)
{
	simd_float3 N = estimateNormal(p, scene);
	simd_float3 L = simd_normalize(light->type.light->point - p);
	simd_float3 V = simd_normalize(eye - p);
	simd_float3 R = simd_normalize(simd_reflect(-L,N));
	
	float dotLN = simd_dot(L, N);
	float dotRV = simd_dot(R, V);
	if (dotLN < 0.0f)
		return simd_make_float3(0.f,0.f,0.f); // Light not visible from this point on the surface
	if(dotRV < 0.0f)
		return light->type.light->i * (K_D * dotLN) * light->color; // Light reflection in opposite direction as viewer, apply only diffuse component
	return light->type.light->i * (K_D * dotLN + K_S * pow(dotRV, ALPHA)) * light->color;
}
simd_float3 phongIllumination(simd_float3 p, simd_float3 eye, t_scene *scene)
{
    simd_float3 color = (scene->amlight->type.light->i * scene->amlight->color * scene->material);
	t_obj *light;
	t_list *tmplist = scene->listlight;
	while(tmplist)
	{
		light = (t_obj *)(tmplist->content);
		float shadow = softshadow(p, (light->type.light->point - p), scene);
		color += phongContribForLight(p, eye, light, scene) * shadow;
		
		tmplist = tmplist->next;
	}
	return simd_clamp(color,0.0f,1.0f);
}

simd_float3		get_normal(simd_float3 eye, simd_float3 dir, t_obj *obj, simd_float3 hit, float dist_i)
{	
	float m, k;
	if (obj->type == 't')
		return (normalize(v_cross(v_minus(TRIANGLE->c1, TRIANGLE->c2),v_minus(TRIANGLE->c1, TRIANGLE->c3))));
	else if (obj->type == 's')
				return (normalize(v_minus(hit, SPHERE->pos)));
	else if (obj->type == 'p')
				return (normalize(PLANE->rot));
	else if (obj->type == 'c')
	{
				m = v_dot(ray.dir, normalize(CYLINDER->rot)) * dist_i + v_dot(v_minus(ray.orig, CYLINDER->pos),normalize(CYLINDER->rot));
				return (normalize((v_minus(v_minus(hit,CYLINDER->pos), v_mult(normalize(CYLINDER->rot), m)))));
	}
	else if (obj->type == 'k')
	{
				k = tan(((CONE->a / 3) * M_PI) / 180);
				m = v_dot(ray.dir, normalize(CYLINDER->rot)) * dist_i + v_dot(v_minus(ray.orig, CYLINDER->pos),normalize(CYLINDER->rot));
				return (normalize((v_minus(v_minus(hit,CYLINDER->pos), v_mult(v_mult(normalize(CYLINDER->rot), m), 1+k*k)))));
	}
	return (_mm_setzero_ps());
}

void	scene_intersect(simd_float3 eye, simd_float3 dir, t_scene *s)
{
	float	dist_i = FLT_MAX;
	t_obj	*closest = NULL;
	float	temp_dist;
	t_scene out;

	while (s->listobj)
	{
		if (((temp_dist = ray_intersect(ray, s->listobj->obj)) < dist_i))
		{
			dist_i = temp_dist;
			closest = listobj->obj;
		}
		s->listobj = listobj->next;
	}
	if (dist_i == FLT_MAX || closest == NULL)
	{
		s->hit = _mm_setzero_ps();
		s->material.color = _mm_setr_ps(0.0, 0.0, 0.0, 0.);
	}
	else
	{
			s->hit =  eye + dir * dist_i;
			s->normal = get_normal(ray, closest, out.hit, dist_i);
			s->material = closest->material;
	}
	return (out);
}

simd_float3	refracted_color(simd_float3 dir, t_scene *s, int depth)
{
	simd_float3 dir = simd_normalize(simd_refract(dir, s->normal, s->material.refractive_index));
	simd_float3 orig = simd_dot(dir, s->normal) < 0 ? s->hit -s->normal * 0.001 : s->hit + s->normal * 0.001;
	return 	(cast_ray(orig, dir, s, depth + 1));
}

simd_float3	reflected_color(simd_float3 dir, t_scene *s, int depth)
{
	simd_float3 dir = simd_normalize(simd_reflect(dir, s->normal));
	simd_float3 orig = simd_dot(dir, s->normal) < 0 ? s->hit -s->normal * 0.001 : s->hit + s->normal * 0.001;
	return 	(cast_ray(orig, dir, s, depth + 1));
}

simd_float3	cast_ray(simd_float3 eye, simd_float3 dir, t_scene *s, int depth)
{
	simd_float3	add_color;
	float diffuse_light_intensity = 0.;
	float specular_light_intensity = 0.;
	simd_float3			refract_col;
	simd_float3			reflect_col;	
	t_scene			scene;
	t_scene			s_shadow;
	simd_float3			color;
	simd_float3 		shadow_dir;
	simd_float3		shadow_orig;
	simd_float3			tmp_vec = vector3(0.0f,0.0f,0.0f);
	const simd_float3	initial_dir = dir;
	scene = scene_intersect(eye, dir, s->listobj);

	if (depth > 4 || (memcmp(&scene.hit, &tmp_vec, sizeof(simd_float3)) == 0))
		return (vector3(0.0f,0.0f,0.0f));
	//add_color = all_color_add(listlight); // C moch
	add_color = vector3(1.f, 1.f, 1.f);

	refract_col = refracted_color(dir, s, depth);
	reflect_col = reflected_color(dir, s, depth);
	while (s->listlight)
	{
		dir = simd_normalize(LIGHT->pos - scene.hit);
		shadow_orig = simd_dot(dir, s->normal) < 0 ? s->hit - s->normal * 0.001 : scene.hit + scene.normal * 0.001;
		shadow_dir = dir;
		s_shadow = scene_intersect(shadow_orig, shadow_dir, s->listobj);
		if ((memcmp(&s_shadow->hit, &tmp_vec, sizeof(simd_float3)) == 0))
		{
			diffuse_light_intensity += LIGHT->intensity * maxf(0., simd_dot(dir, s->normal));
			specular_light_intensity += powf(MAX(0.f, simd_dot(simd_reflect(dir, scene.normal), initial_dir)), scene.material.specular_expo) * LIGHT->intensity;
		}
		s->listlight = s->listlight->next;
	}
	dir = initial_dir;
	color = scene.material.color * (diffuse_light_intensity * s->material.albedo.x) + add_color * (specular_light_intensity * s->material.albedo.y) + reflect_col * s->material.albedo.z + refract_col * s->material.albedo.w;
	return (color);
}

int render(t_scene *scene)
{
    if (STATE == 0)
        eye = get_camera(scene->listcam->content);
    simd_float3x3 viewToWorld = viewMatrix(eye->point, eye->point + vector3(0.f, 0.f, -1.f), vector3(0.f, 1.f, 0.f));
    int bits, size, end;
    void *framebuffer_pre = mlx_new_image(scene->mlx_ptr, scene->width, scene->height);
    unsigned int *framebuffer = (unsigned int *)mlx_get_data_addr(framebuffer_pre, &bits, &size, &end);
    for (int x = 0; x < scene->width; x++)
    {
        for (int y = 0; y < scene->height; y++)
        {
            simd_float3 vue = vector3((float)((x + 0.5f) - scene->width / 2.f), (float)(-(y + 0.5f) + scene->height / 2.f), (float)(-scene->height / (2 * tan(eye->fov / 2.f))));
            simd_float3 dir = simd_normalize(vue);
            simd_float3 worldDir = matrix_multiply(viewToWorld, dir);
			simd_float3 color = cast_ray(eye->point, worldDir, scene, 0);
			framebuffer[x + y * size / 4] = color_to_int(color);

            // float dist = shortestDistanceToSurface(eye->point, worldDir, scene);
            // if (dist >= MAX_DIST)
            //         framebuffer[x + y * size / 4] = color_to_int(simd_make_float3(0.f,0.f,0.f));
            // else
            // {
            //     simd_float3 p = eye->point + dist * worldDir;
            //     simd_float3 color = phongIllumination(p, eye->point, scene);
            //     framebuffer[x + y * size / 4] = color_to_int(color);
            // }
        }
    }
    mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, framebuffer_pre, 0, 0);
    mlx_destroy_image(scene->mlx_ptr, framebuffer_pre);
    return (0);
}

int main(int ac, char **av)
{
	t_scene *scene = NULL;
	if (ac > 1)
		scene = build_rt(av[1]);
	if (scene)
	{
		scene->win_ptr = mlx_new_window(scene->mlx_ptr, scene->width, scene->height, "miniRT");
		mlx_hook(scene->win_ptr, KeyPress, KeyPressMask, deal_key, NULL);
		render(scene);
		//mlx_loop_hook(scene->mlx_ptr, render, scene);
		mlx_loop(scene->mlx_ptr);
	}
	return (0);
}
