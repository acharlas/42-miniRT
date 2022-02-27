/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:05:10 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:05:10 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_countword(const char *str, char c)
{
	int i;
	int word;

	i = 0;
	word = 0;
	if (*str && str[i] != c)
	{
		word++;
		i++;
	}
	if (*str)
		i++;
	while (str[i])
	{
		if (str[i - 1] == c && str[i] != c)
			word++;
		i++;
	}
	return (word);
}

static char		*malloc_word(char const *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	(void)ft_strlcpy(word, str, i + 1);
	return (word);
}

char			**ft_split(char const *s, char c)
{
	char		**tab;
	int			i;

	if (!s || !(tab = malloc(sizeof(char*) * (ft_countword(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(tab[i] = malloc_word(s, c)))
			{
				while (--i >= 0)
					free(tab[i]);
				free(tab);
				return (NULL);
			}
			s += ft_strlen(tab[i++]);
		}
	}
	tab[i] = NULL;
	return (tab);
}
