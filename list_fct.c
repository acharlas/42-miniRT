/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 10:35:00 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/17 16:20:33 by acharlas         ###   ########.fr       */
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

t_list	*ft_lstnew(void *content, char *c)
{
	t_list	*list;

	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->data = content;
	list->next = NULL;
	list->name = c;
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

int	calcule_dist(float dist_i, t_dist t_dist)
{
	return (dist_i < t_dist.cy_dist && dist_i < t_dist.pl_dist && dist_i < t_dist.sp_dist && dist_i < t_dist.co_dist && dist_i < t_dist.tr_dist);
}

t_dist init_dist(void)
{
	t_dist out;

	out.sp_dist = FLT_MAX;
	out.co_dist = FLT_MAX;
	out.cy_dist = FLT_MAX;
	out.pl_dist = FLT_MAX;
	out.tr_dist = FLT_MAX;
	return (out);
}