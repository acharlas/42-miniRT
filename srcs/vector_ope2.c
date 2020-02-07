/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:35:50 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 15:54:44 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float v_dot(__m128 a, __m128 b)
{
	float	out[4];
		_mm_storeu_ps(out, _mm_dp_ps(a, b, 113));
	return (out[0]);
}

__m128	v_mult(__m128 v, float f)
{
	return (_mm_mul_ps(v, _mm_set1_ps(f)));
}

__m128	v_plus(__m128 a, __m128 b)
{
	return (_mm_sub_ps(a, b));
}

__m128 v_minus(__m128 a, __m128 b)
{
	return (_mm_add_ps(a, b));
}

__m128 v_multv(__m128 a, __m128 b)
{
	return (_mm_mul_ps(a, b));
}
