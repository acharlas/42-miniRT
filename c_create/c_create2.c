/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_create2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:32:12 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 16:35:30 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	c_light(t_list **alst, vect3f pos, vect3f color, float intensity)
{
	t_light *light;

	light = malloc(sizeof(t_light));
	light->pos = pos;
	light->intensity = intensity;
	light->color = color;
	ft_lstadd_front(alst, ft_lstnew(light, "l"));
}

t_material 	c_material(vect3f color, vect4f albedo, float refrac_ind, float spec_expo)
{
	t_material material;

	material.color = color;
	material.albedo = albedo;
	material.refractive_index = refrac_ind;
	material.specular_expo = spec_expo;
	return (material);
}
