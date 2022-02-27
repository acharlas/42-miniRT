/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:11:22 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:11:23 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_memeq(void *p1, void *p2)
{
	return ((p1 - p2));
}

void		*p_malloc(size_t size, int add_to_lst, char *obj_type)
{
	void	*out;

	if (!(out = malloc(size)))
		error_handling(ALLOC_FAIL, obj_type);
	if (add_to_lst)
		ft_lstadd_front(&g_alloc_lst, ft_lstnew(out));
	return (out);
}

void		p_free(void *tofree)
{
	ft_lst_remove_if(&g_alloc_lst, tofree, ft_memeq);
}

void		error_handling(enum e_errors err, char *obj_type, ...)
{
	va_list	ap;

	va_start(ap, obj_type);
	if (err == BAD_COORD)
		ft_fdprintf(STDERR_FILENO, "ERROR %d : Bad coordinates for %s %s.\n",\
				err, obj_type, va_arg(ap, char *));
	else if (err == BAD_NB_PARAM)
		ft_fdprintf(STDERR_FILENO, "ERROR %d : Invalid number of parameters \
for %s%s.\n", err, obj_type, va_arg(ap, char *));
	else if (err == ALREADY_SET)
		ft_fdprintf(STDERR_FILENO, "ERROR %d : %s was set more than once.\n",
				err, obj_type);
	else if (err == OUT_OF_RANGE)
		ft_fdprintf(STDERR_FILENO, "ERROR %d : Value out of range for %s%s.\n",
				err, obj_type, va_arg(ap, char *));
	else if (err == INVALID_VALUE)
		ft_fdprintf(STDERR_FILENO, "ERROR %d : Invalid value for %s%s.\n",\
			err, obj_type, va_arg(ap, char *));
	else if (err == ALLOC_FAIL)
		if (ft_fdprintf(STDERR_FILENO, "ERROR %d : Malloc failed \
trying to add : %s.\n", err, obj_type) == -1)
			perror(strerror(ENOMEM));
	va_end(ap);
	cleanup(err);
}

void		cleanup(int exitcode)
{
	extern t_scene *g_scene;

	if (exitcode == 0 && g_scene && g_scene->win_ptr)
		mlx_destroy_window(g_scene->mlx_ptr, g_scene->win_ptr);
	if (g_scene)
	{
		ft_lstclear(&g_scene->listobj, free);
		ft_lstclear(&g_scene->listcam, free);
		ft_lstclear(&g_scene->listlight, free);
		free(g_scene->amlight);
		free(g_scene->mlx_ptr);
	}
	if (g_alloc_lst)
		ft_lstclear(&g_alloc_lst, free);
	exit(exitcode);
}
