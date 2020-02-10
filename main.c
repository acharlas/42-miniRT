/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:02:26 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/10 13:33:03 by rdeban           ###   ########.fr       */
/*   Updated: 2020/02/07 11:47:16 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"

int		main(void)
{
	void *mlx_ptr = mlx_init();
	void *mlx_win = mlx_new_window(mlx_ptr, Width, Height, "miniRT");
	int a, b;
	void *menu1_addr = mlx_png_file_to_image(mlx_ptr, "Menu1.png", &a, &b);
	void *menu1 = mlx_new_image(mlx_ptr, 261, 221);

	
	t_list *objet = NULL;
	t_list *listlight = NULL;

	t_material ivoire = c_material(_mm_setr_ps(0.4, 0.4, 0.3, 0.), c_vect4f(0.6, 0.3, 0.1, 0), 1.0, 50.);
	t_material redrubber = c_material(_mm_setr_ps(1, 0.96, 0.0, 0.), c_vect4f(0.38, 0.05, 0.0, 0), 1.0, 10.);
	t_material glass = c_material(_mm_setr_ps(0.6, 0.9, 0.8, 0.), c_vect4f(0, 0.5, 0.1, 0.8), 1.5, 125.);
	t_material mirroir = c_material(_mm_setr_ps(1, 1, 1, 0.), c_vect4f(0, 10.0, 0.8, 0), 1.0, 1425.);
	t_material plane = c_material(_mm_setr_ps(0.3, 0.2, 0.1, 0.), c_vect4f(0.8, 0.25, 0.01, 0.0), 1.0, 100.);
	t_material blackrubber = c_material(_mm_setr_ps(0.01,0.01,0.01, 0.), c_vect4f(0.9,0.1,0.0,0), 1.0, 10);
	t_material fluo = c_material(_mm_setr_ps(0.01,0.45,0.001, 0.), c_vect4f(0.9, 0.7,0.6,0), 1.0, 125.);

	//c_triangle(&objet, _mm_setr_ps(5,-4,-10, 0.),_mm_setr_ps(0,-4,-15, 0.),_mm_setr_ps(-5,-4,-10, 0.), plane);
	//c_cylinder(&objet, _mm_setr_ps(0, 0,-15, 0.), _mm_setr_ps(0,1,0, 0.), plane, 1, 5);
	//c_cylinder(&objet, _mm_setr_ps(0, 2.6,-13, 0.), _mm_setr_ps(2,1,0, 0.), mirroir, 0.2, 50);
	//c_cone(&objet, _mm_setr_ps(-10, 5, -30, 0.), _mm_setr_ps(1, 1, 0, 0.), plane, 30);
	c_plane(&objet, _mm_setr_ps(0, -6, 0, 0.), _mm_setr_ps(0, 1, 0, 0.), plane);
	//c_sphere(&objet, _mm_setr_ps(-1, 2.6, -12, 0.), redrubber, 1.2);
	//c_sphere(&objet, _mm_setr_ps(0, 0, -16, 0.), ivoire, 2);
	//c_sphere(&objet, _mm_setr_ps(3, 0, -15, 0.), glass, 3);
	//c_sphere(&objet, _mm_setr_ps(3, 0, -15, 0.), blackrubber, 1);
	//c_sphere(&objet, _mm_setr_ps(7, 5, -18, 0.), mirroir, 4);
	c_light(&listlight, _mm_setr_ps(0, 0, -10, 0.), _mm_setr_ps(1, 1, 1, 0.), 1.5);
	c_light(&listlight, _mm_setr_ps(30, 50, -25, 0.), _mm_setr_ps(1, 1, 1, 0.), 1.8);
	c_light(&listlight, _mm_setr_ps(30, 20, 30, 0.), _mm_setr_ps(1, 1, 1, 0.), 0.8);
	//c_light(&listlight, _mm_setzero_ps(), _mm_setr_ps(1, 1, 1, 0.), 2.1);
	//add_objet(&objet, "objet/duck.obj", redrubber);
	t_par par = {mlx_ptr, mlx_win, objet, listlight, menu1_addr, 2};
	mlx_hook(mlx_win, KeyPress, KeyPressMask, deal_key, &par);
	mlx_hook(mlx_win, ButtonPress, ButtonPressMask, deal_button, &par);
	mlx_loop_hook(mlx_ptr, render, &par);
	//render(&par);
	mlx_loop(mlx_ptr);
	// }
}
