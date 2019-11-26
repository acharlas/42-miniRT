/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:13:03 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/26 17:33:42 by acharlas         ###   ########.fr       */
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
	// bool		(*ray_intersect)(const vect3f *orig, const vect3f *dir, float *t0, const t_list *listobj);

}				t_sphere;

typedef struct s_camera
{
	vect3f	pos;
	vect3f	cam_o;
	float	fov;
}				t_camera;

typedef  struct s_list
{
	void	*data;
	struct s_list	*next;
}				t_list;

typedef struct s_light
{
	vect3f pos;
	vect3f color;
	float intensity;
}				t_light;

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
t_list	*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **alst, t_list *new);
int			ft_lstsize(t_list *lst);
int			c_color(vect3f a);
void	c_light(t_list **alst, vect3f pos, vect3f color, float intensity);
t_material 	c_material(vect3f color, vect4f albedo, float refrac_ind, float spec_expo);
void	c_sphere(t_list **alst, vect3f pos, t_material material, float r);
vect3f v_multv(vect3f a, vect3f b);
vect3f	v_div(vect3f a, float b);
#endif
