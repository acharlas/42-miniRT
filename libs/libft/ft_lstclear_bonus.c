/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:03:16 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:03:17 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *lstcpy;
	t_list *last;

	if (!lst || !*lst || !del)
		return ;
	lstcpy = *lst;
	last = NULL;
	while (lstcpy)
	{
		if (last)
			free(last);
		last = lstcpy;
		del(lstcpy->content);
		lstcpy = lstcpy->next;
	}
	if (last)
		free(last);
	*lst = NULL;
}
