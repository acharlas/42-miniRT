/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:56:57 by rdeban            #+#    #+#             */
/*   Updated: 2019/12/05 12:04:27 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dest;

	len = ft_strlen(s);
	if (!(dest = malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_memcpy(dest, s, len + 1);
	return (dest);
}

int		actual_gnl(int ret, char **str, char **line)
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

int		get_next_line(int const fd, char **line)
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
		if (g_ret == 1)
			return (1);
		else if (g_ret == 0)
			return (0);
	}
	*line = ft_strdup("");
	return (0);
}
