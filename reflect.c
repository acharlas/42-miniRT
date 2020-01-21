/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:13:43 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 16:14:38 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vect3f reflect(const vect3f *I, const vect3f *N)
{
	vect3f out;
	out = v_minus(*I, v_mult(*N, (2.f * v_dot(*I, *N))));
    return (out);
}