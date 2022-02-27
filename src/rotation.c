/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:22 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:24 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

simd_float3x3	align_with(simd_float3 align_vec)
{
	simd_float3	s;
	simd_float3 u;
	simd_float3 v;
	simd_float3 w;
	simd_float3 up;

	up = simd_make_float3(0, 1, 0);
	v = simd_abs(simd_cross(align_vec, up));
	w = simd_make_float3(0.f);
	if (ft_memcmp(&v, &w, sizeof(simd_float3)) == 0)
		align_vec.x = 0.0001;
	s = simd_normalize(simd_cross(align_vec, up));
	u = simd_cross(s, align_vec);
	if (ft_memcmp(&v, &w, sizeof(simd_float3)) == 0)
	{
		return (matrix_multiply(rotate_y(radians(90)), simd_matrix(s, u,\
						-align_vec)));
	}
	return (simd_matrix(s, u, -align_vec));
}

simd_float3x3	rotate_x(float theta)
{
	float		c;
	float		s;
	simd_float3 r1;
	simd_float3 r2;
	simd_float3 r3;

	c = cosf(theta);
	s = sinf(theta);
	r1 = simd_make_float3(1, 0, 0);
	r2 = simd_make_float3(0, c, -s);
	r3 = simd_make_float3(0, s, c);
	return (simd_matrix_from_rows(r1, r2, r3));
}

simd_float3x3	rotate_y(float theta)
{
	float		c;
	float		s;
	simd_float3 r1;
	simd_float3 r2;
	simd_float3 r3;

	c = cosf(theta);
	s = sinf(theta);
	r1 = simd_make_float3(c, 0, s);
	r2 = simd_make_float3(0, 1, 0);
	r3 = simd_make_float3(-s, 0, c);
	return (simd_matrix_from_rows(r1, r2, r3));
}

simd_float3x3	rotate_z(float theta)
{
	float		c;
	float		s;
	simd_float3 r1;
	simd_float3 r2;
	simd_float3 r3;

	c = cosf(theta);
	s = sinf(theta);
	r1 = simd_make_float3(c, -s, 0);
	r2 = simd_make_float3(s, c, 0);
	r3 = simd_make_float3(0, 0, 0);
	return (simd_matrix_from_rows(r1, r2, r3));
}
