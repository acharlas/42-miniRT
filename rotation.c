/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:20:48 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/27 18:22:21 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_yaw(float angle, float **vue)
{
	(*vue)[0] = (*vue)[0] * cos(angle) + (*vue)[2] * sin(angle);
	(*vue)[1] = (*vue)[1];
	(*vue)[2] = (*vue)[2] * cos(angle) - (*vue)[0] * sin(angle);
}

void	ft_pitch(float angle, float **vue)
{
	(*vue)[0] = (*vue)[0];
	(*vue)[1] = (*vue)[1] * cos(angle) - (*vue)[2] * sin(angle);
	(*vue)[2] = (*vue)[2] * cos(angle) + (*vue)[1] * sin(angle);
}

void	ft_roll(float angle, float **vue)
{
	(*vue)[0] = (*vue)[0] * cos(angle)  + (*vue)[1] * sin(angle);
	(*vue)[1] = (*vue)[1] * cos(angle)  - (*vue)[0] * sin(angle);
	(*vue)[2] = (*vue)[2];
}
