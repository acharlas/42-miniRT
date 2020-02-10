/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:13:03 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/10 13:28:53 by rdeban           ###   ########.fr       */
/*   Updated: 2020/02/07 11:07:20 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdarg.h>
# include <math.h>
# include "minilibx_mms_20191126_beta/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <float.h>
# include <stdbool.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <immintrin.h>
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"
# include </Users/rdeban/.brew/include/gperftools/profiler.h>
#include <pthread.h>
#define SPHERE ((t_sphere *)obj->data)
#define PLANE ((t_plane *)obj->data)
#define CYLINDER ((t_cylinder *)obj->data)
#define CONE ((t_cone *)obj->data)
#define TRIANGLE ((t_triangle *)obj->data)
#define	LIGHT ((t_light *)(listlight->obj->data))
#define Width 100
#define Height 100
#define FOV M_PI/3

typedef	struct s_vect4f
{
	float i;
	float j;
	float k;
	float l;
}				vect4f;

typedef struct s_material
{
	vect4f	albedo;
	__m128	color;
	float	specular_expo;
	float	refractive_index;
}				t_material;

typedef	struct s_vect2f
{
	float a;
	float b;
}				vect2f;

typedef struct s_sphere
{
	__m128		pos;
	float		r;
}				t_sphere;

typedef struct s_plane
{
	__m128		pos;
	__m128		rot;
}				t_plane;

typedef struct s_cone
{
	__m128		pos;
	__m128		rot;
	float		a;
}				t_cone;

typedef struct	s_cylindr
{
	__m128		pos;
	__m128		rot;
	float		r;
	float		h;
}				t_cylinder;

typedef struct s_triangle
{
	__m128		c1;
	__m128		c2;
	__m128		c3;
}				t_triangle;

typedef struct s_camera
{
	__m128	pos;
	__m128	rot;
	float	fov;
}				t_camera;


typedef struct s_obj
{
	void	*data;
	char	type;
	t_material	material;
}				t_obj;

typedef  struct s_list
{
	t_obj	*obj;
	struct s_list	*next;
}				t_list;

typedef struct s_light
{
	__m128 pos;
	__m128 color;
	float intensity;
}				t_light;

typedef struct	s_ray
{
	__m128		orig;
	__m128		dir;
}				t_ray;

typedef struct s_rt
{
	t_camera	cam;
	t_list		light;
	t_list		obj;
	int			*res;
	int			antiA;
	int			stereo;
}               t_rt;

typedef struct s_scene
{
	__m128	hit;
	__m128	normal;
	t_material material;
}				t_scene;

typedef struct s_par
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_list	*listobj;
	t_list	*listlight;
	void	*menu_img;
	char	state;
}				t_par;

typedef struct s_args
{
	unsigned int *pixel;
	int x;
	int y;
	t_par 		*par;
}				t_args;

int				deal_key(int key, t_par *par);
int				deal_button(int button, int x, int y, t_par *par);
__m128			reflect(const __m128 I, const __m128 n);
__m128			refract(const __m128 I, const __m128 n, const float eta_t, const float eta_i);
t_scene			scene_intersect(t_ray ray, const t_list *listobj);
__m128			cast_ray(t_ray ray, const t_list *listobj, const t_list *listlight, int depth);
__m128			get_normal(t_ray ray, t_obj *obj, __m128 hit, float dist_i);
void			add_objet(t_list **alst, char *str, t_material material);
int				render(t_par *par);
int				ft_isdigit(int c);
unsigned int	ft_strlcpy(char *dest,const char *src, unsigned int size);
__m128			v_cross(__m128 a, __m128 b);
__m128			normalize(__m128 v);
__m128			v_minus(__m128 a, __m128 b);
__m128			v_mult(__m128 a, float b);
__m128			v_plus(__m128 a, __m128 b);
__m128			bg_color(float a, float b, float c);
__m128			verif_color(__m128 color);
vect4f			c_vect4f(float a, float b, float c, float d);
vect2f			c_vect2f(float a, float b);
float			v_dot(__m128 a, __m128 b);
float			maxf(float a, float b);
float			minf(float a, float b);
float			norm(__m128 a);
float 			ft_fabs(float a);
t_list	*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(const t_list *lst);
unsigned int	color_to_int(__m128 v);
void			c_light(t_list **alst, __m128 pos, __m128 color, float intensity);
t_material 		c_material(__m128 color, vect4f albedo, float refrac_ind, float spec_expo);
void			c_sphere(t_list **alst, __m128 pos, t_material material, float r);
__m128			v_multv(__m128 a, __m128 b);
__m128			v_div(__m128 a, float b);
__m128			v_divv(__m128 a, __m128 b);
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
float			minimumfloat(signed int i, ...);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			c_cone(t_list **alst, __m128 pos, __m128 rot ,t_material material, float angle);
void			c_plane(t_list **alst, __m128 pos, __m128 rot ,t_material material);
void			c_cylinder(t_list **alst, __m128 pos, __m128 rot ,t_material material, float r, float h);
float			ray_intersect(t_ray ray, t_obj *obj);
float			ray_intersect_sphere(const __m128 orig, const __m128 dir, const t_sphere sphere);
float			ray_intersect_plane(const __m128 orig, const __m128 dir, const t_plane plane);
float			ray_intersect_cylinder(const __m128 orig, const __m128 dir, const t_cylinder cylinder);
float			ray_intersect_cone(const __m128 orig, const __m128 dir, const t_cone cone);
float			ray_intersect_triangle(const __m128 orig, const __m128 dir, const t_triangle triangle);
void			c_triangle(t_list **alst, __m128 c1, __m128 c2, __m128 c3,t_material material);
void	ft_yaw(float angle, float **vue);
void	ft_pitch(float angle, float **vue);
void	ft_roll(float angle, float **vue);
__m128	antiAliasing(size_t nb_sample, __m128 color, int x, int y, float fov, t_list *listobj, t_list *listlight);
void	cast_ray_thread(void *args);
#endif
