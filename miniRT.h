/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:13:03 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/07 16:24:59 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <mlx.h>
# include "libft/libft.h"

typedef struct	s_rectangle
{
	int	height;
	int	width;
	int	depth;
	int x;
	int y;
} rectangle;

typedef struct	s_sphere
{
	int r;
	int x;
	int y;
} 				t_sphere;

#endif
