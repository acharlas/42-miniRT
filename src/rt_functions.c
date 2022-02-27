/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:12:28 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:12:29 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_functions.h"
#include <sys/param.h>

simd_float3	make_orient(char *orientstr, char *obj_type)
{
	simd_float3	ori;
	char		**ori_s;

	if (!(ori_s = ft_split(orientstr, ',')))
		error_handling(ALLOC_FAIL, obj_type);
	if (ft_stralen(ori_s) != 3)
		error_handling(BAD_NB_PARAM, obj_type, " orientation");
	if (!ft_is_floatstr(ori_s[0]) || !ft_is_floatstr(ori_s[1]) || \
		!ft_is_floatstr(ori_s[2]))
		error_handling(INVALID_VALUE, obj_type, " orientation");
	ori = simd_make_float3(ft_simple_atof(ori_s[0]), ft_simple_atof(ori_s[1]),\
		ft_simple_atof(ori_s[2]));
	ft_straclear(ori_s);
	if (ori.x < -1. || ori.x > 1. || ori.y < -1. || ori.y > 1. || \
		ori.z < -1. || ori.z > 1.)
		error_handling(OUT_OF_RANGE, obj_type, " orientation");
	return (simd_normalize(ori));
}

simd_float3	make_coord(char *coordstr, char *obj_type)
{
	simd_float3	xyz;
	char		**xyz_s;

	if (!(xyz_s = ft_split(coordstr, ',')))
		error_handling(ALLOC_FAIL, obj_type);
	if (ft_stralen(xyz_s) != 3)
		error_handling(BAD_NB_PARAM, obj_type, " positon");
	if (!ft_is_floatstr(xyz_s[0]) || !ft_is_floatstr(xyz_s[1]) || \
		!ft_is_floatstr(xyz_s[2]))
		error_handling(INVALID_VALUE, obj_type, " position");
	xyz = simd_make_float3(ft_simple_atof(xyz_s[0]), ft_simple_atof(xyz_s[1]),\
		ft_simple_atof(xyz_s[2]));
	ft_straclear(xyz_s);
	return (xyz);
}

static int	verify_file(char *rt_path)
{
	int	fd;

	if (ft_strcmp(rt_path + (ft_strlen(rt_path) - 3), ".rt"))
		error_handling(INVALID_VALUE, ".rt file - Invalid file extension", "");
	if ((fd = open(rt_path, O_RDONLY)) == -1)
		error_handling(INVALID_VALUE, ".rt file - Failed to open file", "");
	return (fd);
}

t_scene		*build_rt(char *rt_path)
{
	extern t_scene		*g_scene;
	const char *const	options[] = {"R", "sp", "pl", "tr", "sq", "cy", "c", \
		"l", "A", NULL};
	char				*line;
	char				**info;
	int					fd;

	line = NULL;
	fd = verify_file(rt_path);
	g_scene = scene_init();
	while (get_next_line(fd, &line) > 0 || (ft_strlen(line) > 0))
	{
		if (!(info = ft_split(line, ' ')))
			error_handling(ALLOC_FAIL, "RT");
		if (*info && !ft_is_in_stra(*info, (char **)options))
			error_handling(INVALID_VALUE, ".rt file - Bad element type", "");
		build_scene(g_scene, info);
		ft_straclear(info);
		free(line);
	}
	free(line);
	return (verify_scene(g_scene));
}
