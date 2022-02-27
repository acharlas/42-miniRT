/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:50:58 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:01:00 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t'
			|| c == '\n'
			|| c == '\v'
			|| c == '\f'
			|| c == '\r'
			|| c == ' ')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int i;
	int k;
	int neg;

	i = 0;
	k = 0;
	neg = 1;
	while (ft_isspace(str[k]))
		k++;
	if (str[k] == '+' || str[k] == '-')
	{
		if (str[k] == '-')
			neg *= -1;
		k++;
	}
	while (ft_isdigit(str[k]) && str[k] != '\0')
		i = i * 10 + (str[k++] - 48);
	return (i * neg);
}
