/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ope3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:37:02 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 15:54:54 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

__m128	v_cross(__m128 a, __m128 b)
{
  __m128 a_yzx = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
  __m128 b_yzx = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
  __m128 c = _mm_sub_ps(_mm_mul_ps(a, b_yzx), _mm_mul_ps(a_yzx, b));
  return (_mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1)));
}
