/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:13:43 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/04 15:57:39 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

__m128 reflect(const __m128 I, const __m128 n)
{
	__m128 out;
	out = v_minus(I, v_mult(n, (2.f * v_dot(I, n))));
    return (out);
}
