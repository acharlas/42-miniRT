/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:35:00 by acharlas          #+#    #+#             */
/*   Updated: 2020/02/03 15:37:12 by rdeban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_lstsize(const t_list *lst)
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

t_list	*ft_lstnew(void *content, char c)
{
	t_list	*list;

	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->obj = content;
	list->next = NULL;
	list->obj->type = c;
	return (list);
}

void ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst)
		return ;
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}

float	minimumfloat(signed int i, ...)
{
	va_list ap;
	float	a;
	float	b;

	va_start(ap, i);
	a = va_arg(ap, double);
	while(i != 1)
	{
		b = va_arg(ap, double);
		if (b < a)
			a = b;
		i--;
	}
	va_end(ap);
	return (a);
}
