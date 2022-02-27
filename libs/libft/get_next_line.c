/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:06:38 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:06:39 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

static char			*join(char *s1, char *s2, int len1, int len2)
{
	char *out;

	out = malloc(sizeof(char) * (len1 + len2 + 1));
	ft_memcpy(out, s1, len1);
	ft_memcpy(out + len1, s2, len2);
	out[len1 + len2] = '\0';
	free(s1);
	return (out);
}

static int			actual_gnl(int ret, char **str, char **line)
{
	char	*tofree;
	char	*pos;

	tofree = *str;
	if ((pos = ft_memchr(*str, '\n', ft_strlen(*str))))
	{
		if (pos == *str)
			*line = ft_strdup("");
		else
			*line = ft_substr(*str, 0, pos - *str);
		*str = ft_substr(pos + 1, 0, ft_strlen(pos + 1));
		free(tofree);
		return (1);
	}
	else if (ret < BUFFER_SIZE)
	{
		*line = ft_strdup(*str);
		*str = NULL;
		free(tofree);
		return (0);
	}
	else
		return (-1);
}

int					get_next_line(int const fd, char **line)
{
	static char	*str = NULL;
	char		tmp[BUFFER_SIZE];
	int			ret;
	int			g_ret;

	ret = 0;
	g_ret = 0;
	if (!line || BUFFER_SIZE <= 0 || (read(fd, tmp, 0) == -1))
		return (-1);
	if (!str)
		str = ft_strdup("");
	while (str && ((ret = read(fd, tmp, BUFFER_SIZE)) > 0 || \
				ft_strlen(str) > 0))
	{
		str = join(str, tmp, ft_strlen(str), ret);
		g_ret = actual_gnl(ret, &str, line);
		if (g_ret == 1 || g_ret == 0)
			return (g_ret);
	}
	*line = ft_strdup("");
	return (0);
}
