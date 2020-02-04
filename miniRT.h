/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:13:03 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 10:14:08 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdarg.h>
# include <math.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <float.h>
# include <stdbool.h>
# include <fcntl.h>
# include "get_next_line.h"
#define SPHERE ((t_sphere *)obj->data)
#define PLANE ((t_plane *)obj->data)
#define CYLINDER ((t_cylinder *)obj->data)
#define CONE ((t_cone *)obj->data)
#define TRIANGLE ((t_triangle *)obj->data)
#define	LIGHT ((t_light *)(listlight->obj->data))
#define Width 1024
#define Height 768

typedef	struct s_vect3f
{
	float x;
	float y;
	float z;
}				vect3f;

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
	vect3f	color;
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
	vect3f		pos;
	float		r;
}				t_sphere;

typedef struct s_plane
{
	vect3f		pos;
	vect3f		rot;
}				t_plane;

typedef struct s_cone
{
	vect3f		pos;
	vect3f		rot;
	float		a;
}				t_cone;

typedef struct	s_cylindr
{
	vect3f		pos;
	vect3f		rot;
	float		r;
	float		h;
}				t_cylinder;

typedef struct s_triangle
{
	vect3f		c1;
	vect3f		c2;
	vect3f		c3;
}				t_triangle;

typedef struct s_camera
{
	vect3f	pos;
	vect3f	rot;
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
	vect3f pos;
	vect3f color;
	float intensity;
}				t_light;

typedef struct	s_ray
{
	vect3f		orig;
	vect3f		dir;
	int		depth;
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
	vect3f	hit;
	vect3f	normal;
	t_material material;
}				t_scene;

;
vect3f			reflect(const vect3f I, const vect3f n);
vect3f			refract(const vect3f I, const vect3f n, const float eta_t, const float eta_i);
t_scene			scene_intersect(t_ray ray, const t_list *listobj);
vect3f			cast_ray(t_ray ray, const t_list *listobj, const t_list *listlight, int depth);
vect3f			get_normal(t_ray ray, t_obj *obj, vect3f hit, float dist_i);
void			add_objet(t_list **alst, char *str, t_material material);
void	render(t_list *listobj, t_list *listlight, void *mlx_ptr, void *mlx_win);
int				ft_isdigit(int c);
unsigned int	ft_strlcpy(char *dest,const char *src, unsigned int size);
vect3f			v_cross(vect3f a, vect3f b);
vect3f			c_vect3f(float a, float b, float c);
vect3f			normalize(vect3f this);
vect3f			v_minus(vect3f a, vect3f b);
vect3f			v_mult(vect3f a, float b);
vect3f			v_plus(vect3f a, vect3f b);
vect3f			bg_color(float a, float b, float c);
vect3f			verif_color(vect3f color);
vect4f			c_vect4f(float a, float b, float c, float d);
vect2f			c_vect2f(float a, float b);
float			v_dot(vect3f a, vect3f b);
float			maxf(float a, float b);
float			minf(float a, float b);
float			norm(vect3f a);
float 			ft_fabs(float a);
t_list	*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(const t_list *lst);
int				c_color(vect3f a);
void			c_light(t_list **alst, vect3f pos, vect3f color, float intensity);
t_material 		c_material(vect3f color, vect4f albedo, float refrac_ind, float spec_expo);
void			c_sphere(t_list **alst, vect3f pos, t_material material, float r);
vect3f			v_multv(vect3f a, vect3f b);
vect3f			v_div(vect3f a, float b);
vect3f			v_divv(vect3f a, vect3f b);
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
float			minimumfloat(signed int i, ...);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			c_cone(t_list **alst, vect3f pos, vect3f rot ,t_material material, float angle);
void			c_plane(t_list **alst, vect3f pos, vect3f rot ,t_material material);
void			c_cylinder(t_list **alst, vect3f pos, vect3f rot ,t_material material, float r, float h);
float			ray_intersect(t_ray ray, t_obj *obj);
float			ray_intersect_sphere(const vect3f orig, const vect3f dir, const t_sphere sphere);
float			ray_intersect_plane(const vect3f orig, const vect3f dir, const t_plane plane);
float			ray_intersect_cylinder(const vect3f orig, const vect3f dir, const t_cylinder cylinder);
float			ray_intersect_cone(const vect3f orig, const vect3f dir, const t_cone cone);
float			ray_intersect_triangle(const vect3f orig, const vect3f dir, const t_triangle triangle);
void			c_triangle(t_list **alst, vect3f c1, vect3f c2, vect3f c3,t_material material);
void	ft_yaw(float angle, float **vue);
void	ft_pitch(float angle, float **vue);
void	ft_roll(float angle, float **vue);
#endif
