/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:13:03 by acharlas          #+#    #+#             */
/*   Updated: 2019/12/03 18:51:45 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <float.h>
# include <stdbool.h>
#define SPHERE ((t_sphere *)(listobj)->data)
#define SQUARE ((t_square *)(listobj)->data)
#define CYLINDER ((t_cylinder *)(listobj)->data)


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

typedef struct s_square
{
	vect3f		pos;
	vect2f		taille;
	t_material	material;
	vect3f		rot;
	bool			(*ray_intersect)(const vect3f *, const vect3f *, float *, const struct s_square);
}				t_square;

typedef struct s_cone
{
	vect3f pos;
	
}				t_cone;

typedef struct s_camera
{
	vect3f	pos;
	vect3f	cam_o;
	float	fov;
}				t_camera;

typedef  struct s_list
{
	void	*data;
	int		name;
	struct s_list	*next;
}				t_list;

typedef struct s_light
{
	vect3f pos;
	vect3f color;
	float intensity;
}				t_light;

typedef struct	s_cylinder
{
	vect3f		pos;
	vect3f		rot;
	float		r;
	float		h;
	t_material	material;
	bool			(*ray_intersect)(const vect3f *, const vect3f *, float *, const struct s_cylinder);
}				t_cylinder;

vect3f		c_vect3f(float a, float b, float c);
vect3f		normalize(vect3f this);
vect3f		v_minus(vect3f a, vect3f b);
vect3f		v_mult(vect3f a, float b);
vect3f		v_plus(vect3f a, vect3f b);
vect3f		bg_color(float a, float b, float c);
vect3f		verif_color(vect3f color);
vect4f		c_vect4f(float a, float b, float c, float d);
vect2f		c_vect2f(float a, float b);
float		v_dot(vect3f a, vect3f b);
float		maxf(float a, float b);
float		minf(float a, float b);
float		norm(vect3f a);
float 		ft_fabs(float a);
t_list	*ft_lstnew(void *content, char c);
void ft_lstadd_front(t_list **alst, t_list *new);
int			ft_lstsize(const t_list *lst);
int			c_color(vect3f a);
void	c_light(t_list **alst, vect3f pos, vect3f color, float intensity);
t_material 	c_material(vect3f color, vect4f albedo, float refrac_ind, float spec_expo);
void	c_sphere(t_list **alst, vect3f pos, t_material material, float r, void *f);
vect3f v_multv(vect3f a, vect3f b);
vect3f	v_div(vect3f a, float b);
vect3f	v_divv(vect3f a, vect3f b);
bool		ray_intersect_sphere(const vect3f *orig, const vect3f *dir, float *t0, const t_sphere sphere);
bool		ray_intersect_square(const vect3f *orig, const vect3f *dir, float *t0, const t_square square);

bool	ray_intersect_cylinder(const vect3f *orig, const vect3f *dir, float *t0, const t_cylinder cylinder);

#endif
