/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_create2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:32:12 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/07 09:21:12 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	c_light(t_list **alst, __m128 pos, __m128 color, float intensity)
{
	t_light *light;
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	light = malloc(sizeof(t_light));
	light->pos = pos;
	light->intensity = intensity;
	light->color = color;
	obj->data = light;
	obj->type = 'l';
	ft_lstadd_front(alst, ft_lstnew(obj));
}

t_material 	c_material(__m128 color, vect4f albedo, float refrac_ind, float spec_expo)
{
	t_material material;

	material.color = color;
	material.albedo = albedo;
	material.refractive_index = refrac_ind;
	material.specular_expo = spec_expo;
	return (material);
}
