/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:50:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:00:36 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_FUNCTIONS_H
# define RT_FUNCTIONS_H
# include "minirt.h"

void		add_light(char **info, t_scene *scene);
void		add_ambientlight(char **info, t_scene *scene);
void		add_camera(char **info, t_scene *scene);
void		set_resolution(char **info, t_scene *scene);
void		add_plane(char **info, t_scene *scene);
void		add_sphere(char **info, t_scene *scene);
void		add_triangle(char **info, t_scene *scene);
void		add_square(char **info, t_scene *scene);
void		add_cylinder(char **info, t_scene *scene);
t_scene		*scene_init(void);
t_scene		*verify_scene(t_scene *scene);
void		build_scene(t_scene *scene, char **info);
t_scene		*build_rt(char *rt_path);
simd_float3	make_color(char *colorstr, char *obj_type);
simd_float3	make_coord(char *coordstr, char *obj_type);
simd_float3	make_orient(char *orientstr, char *obj_type);

#endif
