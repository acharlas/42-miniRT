/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:35:00 by acharlas          #+#    #+#             */
/*   Updated: 2019/11/23 11:23:49 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_lstsize(t_listobj *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_listobj	*ft_lstnew(void *content)
{
	t_listobj	*list;

	if (!(list = malloc(sizeof(t_listobj))))
		return (NULL);
	list->data = content;
	list->next = NULL;
	return (list);
}

void ft_lstadd_front(t_listobj **alst, t_listobj *new)
{
	if (!alst)
		return ;
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}
