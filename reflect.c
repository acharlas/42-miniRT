/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:13:43 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/03 15:59:32 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vect3f reflect(const vect3f I, const vect3f n)
{
	vect3f out;
	out = v_minus(I, v_mult(n, (2.f * v_dot(I, n))));
    return (out);
}
