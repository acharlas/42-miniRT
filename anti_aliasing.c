/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:40:43 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/07 11:40:17 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
__m128	antiAliasing(size_t nb_sample, __m128 color, int x, int y, float fov, t_list *listobj, t_list *listlight)
{
	float	inc[2];
	size_t	sample;
	__m128	vue;
	__m128	tmpbuffer;
	int c = 0;

	if (nb_sample < 2)
		return (color);
	inc[0] = 1 / powf((float)nb_sample,2); // faire une variable
	while (inc[0] <= 1 - 1 / powf((float)nb_sample,2))
	{
		inc[1] = 1 / powf((float)nb_sample,2);
		while (inc[1] <= 1 - 1 / powf((float)nb_sample,2))
		{
			vue = _mm_setr_ps((x + inc[0]) - Width / 2, - (y + inc[1]) + Height / 2, - Height / (2. * tan(fov / 2.)), 0.);
			t_ray ray = {_mm_setr_ps(0, 0, 0, 0), normalize(vue)};
			color = _mm_add_ps(color, cast_ray(ray, listobj, listlight, 0));
			inc[1] += 2 / powf((float)nb_sample,2);
			c++;
		}
		inc[0] += 2 / powf((float)nb_sample,2);
	}
	return (_mm_div_ps(color, _mm_set1_ps(c))); // trouver l'equation des couches
}
