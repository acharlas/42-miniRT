/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:10:46 by acharlas          #+#    #+#             */
/*   Updated: 2020/11/08 14:10:48 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdint.h>
#include <endian.h>

static void	set_bmp_header(int fd, int width, int height)
{
	char *bmp_header;

	bmp_header = p_malloc(sizeof(char) * 122, 1, "bmp");
	ft_bzero(bmp_header, 122);
	*(uint16_t *)bmp_header = *(const uint16_t *)"BM";
	*(uint32_t *)(bmp_header + 2) = width * height * 4 + 122;
	*(bmp_header + 10) = 122;
	*(uint32_t *)(bmp_header + 14) = 108;
	*(uint32_t *)(bmp_header + 18) = width;
	*(uint32_t *)(bmp_header + 22) = height;
	*(uint16_t *)(bmp_header + 26) = 1;
	*(uint16_t *)(bmp_header + 28) = 32;
	*(uint32_t *)(bmp_header + 34) = width * height * 4;
	*(uint32_t *)(bmp_header + 38) = 2835;
	*(uint32_t *)(bmp_header + 42) = 2835;
	*(uint32_t *)(bmp_header + 62) = 0x000000FF;
	write(fd, bmp_header, 122);
	p_free(bmp_header);
}

void		mlx_image_to_bmp(unsigned int *img, int size, int width, int height)
{
	int x;
	int y;
	int fd;

	y = height - 1;
	if (!(fd = open("miniRT.BMP", O_CREAT | O_WRONLY, 0644)))
		return ;
	set_bmp_header(fd, width, height);
	while (y >= 0)
	{
		x = 0;
		while (x < width)
		{
			write(fd, &img[x + y * size / 4], 4);
			x++;
		}
		y--;
	}
}
