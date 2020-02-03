#include "miniRT.h"

vect3f		get_normal(t_ray ray, t_obj *obj, vect3f hit, float dist_i)
{	
	float m, k;
	if (obj->type == 't')
		return (normalize(v_cross(v_minus(TRIANGLE->c1, TRIANGLE->c2),v_minus(TRIANGLE->c1, TRIANGLE->c3))));
	else if (obj->type == 's')
				return (normalize(v_minus(hit, SPHERE->pos)));
	else if (obj->type == 'p')
				return (normalize(PLANE->rot));
	else if (obj->type == 'c')
	{
				m = v_dot(ray.dir, normalize(CYLINDER->rot)) * dist_i + v_dot(v_minus(ray.orig, CYLINDER->pos),normalize(CYLINDER->rot));
				return (normalize((v_minus(v_minus(hit,CYLINDER->pos), v_mult(normalize(CYLINDER->rot), m)))));
	}
	else if (obj->type == 'k')
	{
				k = tan(((CONE->a / 2) * M_PI) / 180);
				m = v_dot(ray.dir, normalize(CYLINDER->rot)) * dist_i + v_dot(v_minus(ray.orig, CYLINDER->pos),normalize(CYLINDER->rot));
				return (normalize((v_minus(v_minus(hit,CYLINDER->pos), v_mult(v_mult(normalize(CYLINDER->rot), m), 1+k*k)))));
	}
	return (c_vect3f(0, 0, 0));
}
