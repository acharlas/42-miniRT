/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:13:03 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/25 13:56:29 by acharlas         ###   ########.fr       */
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
}				t_sphere;

typedef struct s_camera
{
	vect3f	pos;
	vect3f	cam_o;
	float	fov;
}				t_camera;

typedef  struct s_listobj
{
	void	*data;
	struct s_listobj	*next;
}				t_listobj;

typedef struct s_light
{
	vect3f pos;
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
t_listobj	*ft_lstnew(void *content);
void		ft_lstadd_front(t_listobj **alst, t_listobj *new);
int			ft_lstsize(t_listobj *lst);
int			c_color(vect3f a);
#endif
