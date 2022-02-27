/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:11 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:12 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	color_to_int(simd_float3 v)
{
	unsigned int color;

	if (v.x > 1)
		v.x = 1;
	if (v.y > 1)
		v.y = 1;
	if (v.z > 1)
		v.z = 1;
	color = (int)(255 * v.x) << 16;
	color |= (int)(255 * v.y) << 8;
	color |= (int)(255 * v.z);
	return (color);
}

simd_float3		make_color(char *colorstr, char *obj_type)
{
	char	**color;
	int		red;
	int		green;
	int		blue;

	if (!(color = ft_split(colorstr, ',')))
		error_handling(ALLOC_FAIL, "color");
	if (ft_stralen(color) != 3)
		error_handling(BAD_NB_PARAM, obj_type, " color");
	if (!ft_is_digitstr(color[0]) || !ft_is_digitstr(color[1]) || \
			!ft_is_digitstr(color[2]))
		error_handling(INVALID_VALUE, obj_type, " color");
	red = ft_atoi(color[0]);
	green = ft_atoi(color[1]);
	blue = ft_atoi(color[2]);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || \
			blue > 255)
		error_handling(OUT_OF_RANGE, obj_type, " color");
	ft_straclear(color);
	return (vector3(red / 255.f, green / 255.f, blue / 255.f));
}
