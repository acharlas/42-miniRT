/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:04:32 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:04:33 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*j_and_free_and_len(char *s1, char *s2, int *len1, int len2)
{
	char	*out;

	out = NULL;
	if (s1 && s2)
		out = ft_special_join(s1, s2, *len1, len2);
	free(s1);
	*len1 += len2;
	return (out);
}

int		write_and_free(int fd, char *s, int len)
{
	int ret;

	ret = write(fd, s, len);
	free(s);
	return (ret);
}
