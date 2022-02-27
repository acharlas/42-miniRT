/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:50:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:00:11 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdarg.h>
# include <math.h>
# include <simd/simd.h>
# include <stdio.h>
# include <errno.h>
# include <float.h>
# include <stdbool.h>
# include <fcntl.h>
# include <immintrin.h>
# ifdef __linux__
#  include <X11/X.h>
#  include "minilibx-linux/mlx.h"
# else
#  include "mlx_metal/mlx.h"
# endif
# include <sys/param.h>
# include "libft/libft.h"
# include "structs.h"
# include "rt_functions.h"
# include "error.h"

float				radians(float degrees);
float				ray_intersect(t_ray ray, t_obj *obj);
t_obj				*scene_intersect(t_ray ray, const t_list *listobj, \
simd_float3 *hit, float *dist_i);
simd_float3			cast_ray(t_ray ray, const t_list *listobj, \
const t_list *listlight, t_scene *scene);
simd_float3			get_normal(t_ray ray, t_obj *obj, simd_float3 hit, \
float dist_i);
int					render(t_scene *scene);
__m128				bg_color(float a, float b, float c);
__m128				verif_color(__m128 color);
float				maxf(float a, float b);
float				minf(float a, float b);
float				ft_fabs(float a);
unsigned int		color_to_int(simd_float3 v);
float				minimumfloat(signed int i, ...);
float				ray_intersect_sphere(t_ray ray, const t_sphere sphere);
float				ray_intersect_plane(t_ray ray, const t_plane plane);
float				ray_intersect_cylinder(t_ray ray,\
const t_cylinder cylinder);
float				ray_intersect_triangle(t_ray ray, t_triangle triangle);
float				ray_intersect_square(t_ray ray, t_square square);
float				ft_fabs(float a);
simd_float3x3		rotate_x(float theta);
simd_float3x3		rotate_y(float theta);
simd_float3x3		rotate_z(float theta);
simd_float3x3		align_with(simd_float3 align_vec);
void				mlx_image_to_bmp(unsigned int *img, int size, int width,\
int height);
int					deal_key(int key, t_scene *scene);
t_camera			*get_camera(t_obj *obj);
int					close_mlx(t_scene *scene);
int					handle_mini(t_scene *scene);
void				p_free(void *tofree);
float				ft_simple_atof(const char *str);
void				cleanup(int exitcode);

extern t_list *g_alloc_lst;

#endif
