#include "miniRT.h"

void add_object_to_scene(__m128 camera_pos, t_obj *obj, t_list *listobj)
{
	t_material redrubber = c_material(_mm_setr_ps(1, 0.96, 0.0, 0.), c_vect4f(0.38, 0.02, 0.0, 0), 1.0, 10.);
	c_sphere(&listobj, camera_pos, redrubber, 1);
}

//print();
//int deal_mouse(int x, int y, void *param)
//{
//	struct params par = *(struct params *)param;
//	int u, v;
//	//mlx_mouse_move(par.win_ptr, 0, 0);
//	mlx_mouse_get_pos(par.win_ptr, &u, &v);
//	printf("mouse x == %d -- mouse y == %d\n", u, v);
//	mlx_clear_window(par.mlx_ptr, par.win_ptr);
//	mlx_put_image_to_window(par.mlx_ptr, par.win_ptr, par.img, x - 25, y - 25);
//	return (0);
//}
//
//int print_key(int key, void *param)
//{
//	struct params par = *(struct params *)param;
//	*par.keyrel = 0;
//	return (0);
//}

int deal_key(int key, t_par *par)
{
	if (key == 8)
	{
		par->state = 1;
		mlx_string_put(par->mlx_ptr, par->win_ptr, 10, Height - 100, 0x000000, "Press the key corresponding to \n the object you wish to add : {s = sphere}");
	}
	else if (key == 1 && par->state == 1)
		mlx_string_put(par->mlx_ptr, par->win_ptr, 10, Height - 90, 0x000000, "You are now adding a sphere, please use the mouse to choose where to add the sphere");
	else if (key == 53)
		exit(0);
	return (0);
}

int deal_button(int button, int x, int y, t_par *par)
{
	char *a;
	__m128 vue;
	t_material redrubber = c_material(_mm_setr_ps(1, 0.96, 0.0, 0.), c_vect4f(0.38, 0.02, 0.0, 0), 1.0, 10.);
	if (button == 1 && par->state == 1)
		//vue = _mm_setr_ps((x + 0.5) - Width / 2, - (y + 0.5) + Height / 2, 25, 0.);
		c_sphere(&par->listobj, _mm_setr_ps(-1, -2.6, -12, 0.), redrubber, 1.2);
		//c_sphere(&par->listobj, _mm_sub_ps(_mm_setzero_ps(), vue), redrubber, 1);
	par->state = 2;
	return (0);
}
