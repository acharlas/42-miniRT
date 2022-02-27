/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:50:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:00:40 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minirt.h"
# include <time.h>
# include "libft/libft.h"

typedef struct	s_args
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_list			*listobj;
	struct timespec *ts_start;
	struct timespec *ts_end;
}				t_args;

typedef struct	s_ray
{
	simd_float3		orig;
	simd_float3		dir;
}				t_ray;

typedef struct	s_sphere
{
	simd_float3	orig;
	float		diameter;
}				t_sphere;

typedef struct	s_plane
{
	simd_float3 orig;
	simd_float3 orient;
}				t_plane;

typedef struct	s_square
{
	simd_float3 orig;
	simd_float3 orient;
	float		height;
}				t_square;

typedef struct	s_cylinder
{
	simd_float3 orig;
	simd_float3 orient;
	float		diameter;
	float		height;
}				t_cylinder;

typedef struct	s_triangle
{
	simd_float3 a;
	simd_float3 b;
	simd_float3 c;
}				t_triangle;

typedef struct	s_camera
{
	simd_float3 orig;
	simd_float3 orient;
	float		fov;
}				t_camera;

typedef struct	s_light
{
	simd_float3 orig;
	float		i;
}				t_light;

union			u_obj_type
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_square	*square;
	t_cylinder	*cylinder;
	t_triangle	*triangle;
	t_light		*light;
};

enum			e_obj_type_id
{
	SPHERE,
	PLANE,
	SQUARE,
	CYLINDER,
	TRIANGLE,
	LIGHT
};

enum			e_rendermode
{
	SAVETOFILE,
	NOCHANGE,
	TORENDER
};

typedef struct	s_obj
{
	enum e_obj_type_id		id;
	union u_obj_type		type;
	simd_float3				color;
}				t_obj;

typedef struct	s_scene
{
	int					width;
	int					height;
	t_obj				*amlight;
	t_list				*listobj;
	t_list				*listcam;
	t_list				*listlight;
	void				*mlx_ptr;
	void				*win_ptr;
	enum e_rendermode	rend;
}				t_scene;

typedef struct	s_frame
{
	t_camera		*eye;
	simd_float3		vue;
	t_ray			ray;
	unsigned int	*buffer;
	void			*ptr;
	int				info[3];
}				t_frame;

#endif
