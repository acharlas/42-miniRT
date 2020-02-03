/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/03 19:26:04 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		main(void)
{
	const int width = 1024;
	const int height = 768;
	void *mlx_ptr = mlx_init();
	void *mlx_win = mlx_new_window(mlx_ptr, Width, Height, "miniRT");
	
	t_list *objet = NULL;
	t_list *listlight = NULL;

	t_material ivoire = c_material(c_vect3f(0.4, 0.4, 0.3), c_vect4f(0.6, 0.3, 0.1, 0), 1.0, 50.);
	t_material redrubber = c_material(c_vect3f(1, 0.96, 0.0), c_vect4f(0.38, 0.02, 0.0, 0), 1.0, 10.);
	t_material glass = c_material(c_vect3f(0.6, 0.9, 0.8), c_vect4f(0, 0.5, 0.1, 0.8), 1.5, 125.);
	t_material mirroir = c_material(c_vect3f(1, 1, 1), c_vect4f(0, 10.0, 0.8, 0), 1.0, 1425.);
	t_material plane = c_material(c_vect3f(0.3, 0.2, 0.1), c_vect4f(0.8, 0.25, 0.0, 0.0), 1.0, 100.);
	t_material blackrubber = c_material(c_vect3f(0.01,0.01,0.01), c_vect4f(0.9,0.1,0.0,0), 1.0, 10);
	t_material fluo = c_material(c_vect3f(0.01,0.45,0.001), c_vect4f(0.9, 0.7,0.6,0), 1.0, 125.);

	// c_triangle(&objet, c_vect3f(5,-4,-10),c_vect3f(0,-4,-15),c_vect3f(-5,-4,-10), plane);
	// c_cylinder(&objet, c_vect3f(0, 0,-15), c_vect3f(0,1,0), plane, 1, 5);
	// c_cone(&objet, c_vect3f(-10, 5, -30), c_vect3f(1, 1, 0), plane, 30);
	// c_plane(&objet, c_vect3f(0, -5, 0), c_vect3f(0, 1, 0), plane);
	c_sphere(&objet, c_vect3f(-1, 2.6, -12), redrubber, 1.2);
	c_sphere(&objet, c_vect3f(0, 0, -16), ivoire, 2);
	c_sphere(&objet, c_vect3f(3, 0, -15), glass, 3);
	c_sphere(&objet, c_vect3f(3, 0, -15), blackrubber, 1);
	// c_sphere(&objet, c_vect3f(7, 5, -18), mirroir, 4);
	c_light(&listlight, c_vect3f(-20, 20, 20), c_vect3f(1, 1, 1), 1.5);
	c_light(&listlight, c_vect3f(30, 50, -25), c_vect3f(1, 1, 1), 1.8);
	c_light(&listlight, c_vect3f(30, 20, 30), c_vect3f(1, 1, 1), 0.8);
	// c_light(&listlight, c_vect3f(0, 0, 0), c_vect3f(1, 1, 1), 2.1);


	// add_objet(&objet, "cube.obj", redrubber);
	render(objet, listlight, mlx_ptr, mlx_win);
	mlx_loop(mlx_ptr);
}
