/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_objet.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:19:09 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 21:27:15 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	add_objet(t_list **alst, char *str, t_material material)
{
	char ***tab;
	char **array;
	char *line;
	int fd = open(str, O_RDONLY);
	int i = 0;
	float a;
	float b;
	float c;
	tab = malloc(sizeof(char ***) * 8);
	while(get_next_line(fd, &line) && i != 8)
	{
		tab[i] = ft_split(line, ' ');
		i++;
	}
	i = 0;
	float x = 0;
	float y = 0;
	float z = 3;
	float div = 1;
	float alpha = 0;
	while (get_next_line(fd, &line))
	{
		array = ft_split(line, ' ');
		a = atof(tab[atoi(array[1]) - 1][1]) / div ;
		b = atof(tab[atoi(array[1]) - 1][2]) / div ;
		c = atof(tab[atoi(array[1]) - 1][3]) / div ;
		vect3f m = c_vect3f(a - x,  b - y,  c - z);
		a = atof(tab[atoi(array[2]) - 1][1]) / div ;
		b = atof(tab[atoi(array[2]) - 1][2]) / div ;
		c = atof(tab[atoi(array[2]) - 1][3]) / div ;
		vect3f n = c_vect3f(a - x, b - y, c - z);
		a = atof(tab[atoi(array[3]) - 1][1]) / div ;
		b = atof(tab[atoi(array[3]) - 1][2]) / div ;
		c = atof(tab[atoi(array[3]) - 1][3]) / div ;
		vect3f o = c_vect3f(a - x, b - y, c - z);
		c_triangle(alst, m, n, o, material);
	}
	free(tab);
}