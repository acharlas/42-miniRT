/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:00:18 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:00:23 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minirt.h"

enum	e_errors
{
	BAD_NB_PARAM = 1,
	BAD_COORD,
	INVALID_VALUE,
	ALREADY_SET,
	OUT_OF_RANGE,
	ALLOC_FAIL,
};

void	error_handling(enum e_errors err, char *obj_type, ...);
void	*p_malloc(size_t size, int add_to_lst, char *obj_type);
#endif
