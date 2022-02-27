/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:05:14 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:05:15 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_straclear(char **stra)
{
	char	*tofree;
	int		i;

	if (!stra)
		return ;
	i = 0;
	while (stra[i])
	{
		tofree = stra[i];
		i++;
		free(tofree);
		tofree = NULL;
	}
	free(stra);
}
