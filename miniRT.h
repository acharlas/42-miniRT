/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:13:03 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 16:30:41 by acharlas         ###   ########.fr       */
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
#define SPHERE ((t_sphere *)(listobj)->data)
#define PLANE ((t_plane *)(listobj)->data)
#define CYLINDER ((t_cylinder *)(listobj)->data)
#define CONE ((t_cone *)(listobj)->data)
#define TRIANGLE ((t_triangle *)(listobj)->data)

typedef	struct s_dist
{
	float	sp_dist;
	float	pl_dist;
	float	cy_dist;
	float	co_dist;
	float	tr_dist;
}				t_dist;

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
	t_material	material;
	float		r;
	bool		(*ray_intersect)(const vect3f *, const vect3f *, float *, const struct s_sphere);

}				t_sphere;

typedef struct s_plane
{
	vect3f		pos;
	t_material	material;
	vect3f		rot;
	bool		(*ray_intersect)(const vect3f *, const vect3f *, float *, const struct s_plane);
}				t_plane;

typedef struct s_cone
{
	vect3f		pos;
	vect3f		rot;
	t_material	material;
	float		a;
	bool		(*ray_intersect)(const vect3f *, const vect3f *, float *, const struct s_cone);
}				t_cone;

typedef struct	s_cylinder
{
	vect3f		pos;
	vect3f		rot;
	float		r;
	float		h;
	t_material	material;
	bool			(*ray_intersect)(const vect3f *, const vect3f *, float *, const struct s_cylinder);
}				t_cylinder;

typedef struct s_triangle
{
	vect3f		c1;
	vect3f		c2;
	vect3f		c3;
	t_material	material;
	bool		(*ray_intersect)(const vect3f *, const vect3f *, float *, const struct s_triangle);
}				t_triangle;

typedef struct s_camera
{
	vect3f	pos;
	vect3f	cam_o;
	float	fov;
}				t_camera;

typedef  struct s_list
{
	void	*data;
	char	*name;
	struct s_list	*next;
}				t_list;

typedef struct s_light
{
	vect3f pos;
	vect3f color;
	float intensity;
}				t_light;

vect3f			reflect(const vect3f *I, const vect3f *N);
vect3f			refract(const vect3f *I, const vect3f *n, const float eta_t, const float eta_i);
int				scene_intersect(const vect3f *orig, const vect3f *dir, const t_list *listobj, vect3f *hit, vect3f *n, t_material *material);
vect3f			cast_ray(const vect3f orig, const vect3f dir, const t_list *listobj, const t_list *listlight, size_t depth);
void			add_objet(t_list **alst, char *str, t_material material);
void			*render(t_list *listobj, t_list *listlight, const int width, const int height);
t_dist			init_dist(void);
int				calcule_dist(float dist_i, t_dist t_dist);
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
t_list			*ft_lstnew(void *content, char *c);
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
bool			ray_intersect_sphere(const vect3f *orig, const vect3f *dir, float *t0, const t_sphere sphere);
bool			ray_intersect_plane(const vect3f *orig, const vect3f *dir, float *t0, const t_plane plane);
bool			ray_intersect_cylinder(const vect3f *orig, const vect3f *dir, float *t0, const t_cylinder cylinder);
bool			ray_intersect_cone(const vect3f *orig, const vect3f *dir, float *t0, const t_cone cone);
bool			ray_intersect_triangle(const vect3f *orig, const vect3f *dir, float *t0, const t_triangle triangle);
void			c_triangle(t_list **alst, vect3f c1, vect3f c2, vect3f c3,t_material material);
#endif
