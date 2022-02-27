/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_stra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:03:01 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:03:03 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_to_stra(t_list *lst)
{
	char	**stra;
	char	**out;
	int		i;

	if (!lst)
		return (NULL);
	i = ft_lstsize(lst);
	stra = malloc(sizeof(char *) * i + 1);
	out = stra;
	while (lst)
	{
		*stra++ = ft_strdup(lst->content);
		lst = lst->next;
	}
	*stra = NULL;
	return (out);
}
