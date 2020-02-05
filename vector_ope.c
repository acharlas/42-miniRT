/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:10:46 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/05 08:15:10 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vect4f	c_vect4f(float a, float b, float c, float d)
{
	vect4f	out;
	
	out.i = a;
	out.j = b;
	out.k = c;
	out.l = d;
	return (out);
}

__m128 normalize_inacc(__m128 v)
{
  __m128 inverse_norm = _mm_rsqrt_ps(_mm_dp_ps(v, v, 127));
  return (_mm_mul_ps(v, inverse_norm));
}

__m128	normalize(__m128 v)
{
    return (_mm_div_ps(v, _mm_sqrt_ps(_mm_dp_ps(v, v, 127))));
}
