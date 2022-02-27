/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:02:55 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:02:57 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	process(t_list **begin_list, t_list *prev, t_list **lst)
{
	if (*lst == *begin_list)
	{
		*begin_list = (*lst)->next;
		prev = *begin_list;
	}
	else if (prev)
		prev->next = (*lst)->next ? (*lst)->next : NULL;
	free((*lst)->content);
	free(*lst);
	*lst = (prev == *begin_list) ? *begin_list : prev->next;
}

void		ft_lst_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*lst;
	t_list	*prev;

	prev = NULL;
	if (!begin_list || !data_ref || !cmp)
		return ;
	lst = *begin_list;
	while (lst)
	{
		if ((cmp(data_ref, lst->content) == 0))
		{
			process(begin_list, prev, &lst);
			continue;
		}
		else
			prev = lst;
		lst = lst->next;
	}
}
