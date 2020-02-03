/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:14:54 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/03 15:58:35 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vect3f	refract(const vect3f I, const vect3f n, const float eta_t, const float eta_i)
{
	float cosi = -maxf(-1., minf(1., v_dot(I, n)));
	if (cosi < 0)
	{
		vect3f m = v_minus(c_vect3f(0,0,0), n);
		return (refract(I, n, eta_i, eta_t));
	}
	float eta = (eta_i / eta_t);
	float k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? c_vect3f(1,0,0) : v_plus(v_mult(I,eta), v_mult(n,eta*cosi -sqrtf(k)));
}
