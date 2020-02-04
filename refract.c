/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:14:54 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 16:55:53 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

__m128	refract(const __m128 I, const __m128 n, const float eta_t, const float eta_i)
{
	float cosi = -maxf(-1., minf(1., v_dot(I, n)));
	if (cosi < 0)
	{
		__m128 m = v_minus(_mm_setzero_ps(), n);
		return (refract(I, m, eta_i, eta_t));
	}
	float eta = (eta_i / eta_t);
	float k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? _mm_setr_ps(1,0,0, 0) : v_plus(v_mult(I,eta), v_mult(n,eta*cosi -sqrtf(k)));
}
