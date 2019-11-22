/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:13:03 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/22 17:56:42 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <mlx.h>

typedef	struct s_struct
{
	float x;
	float y;
	float z;
}				vect3f;

typedef struct s_sphere
{
	vect3f	pos;
	float	r;
	vect3f	color;
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

#endif
