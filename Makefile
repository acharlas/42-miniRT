# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/06 14:10:31 by acharlas          #+#    #+#              #
#    Updated: 2020/02/07 07:43:34 by acharlas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = srcs/anti_aliasing.c \
srcs/fct_annext.c \
srcs/ft_atoi.c \
srcs/ft_isdigit.c \
srcs/ft_split.c \
srcs/ft_strcpm.c \
srcs/ft_strlcpy.c \
srcs/get_next_line.c \
srcs/get_next_line_utils.c \
srcs/init_rt.c \
srcs/list_fct.c \
srcs/main.c \
srcs/new_cast_ray.c \
srcs/new_scene_intersect.c \
srcs/newrender.c \
srcs/normal.c \
srcs/ray_intersect.c \
srcs/reflect.c \
srcs/refract.c \
srcs/rotation.c \
srcs/vector_ope.c \
srcs/vector_ope2.c \
srcs/vector_ope3.c  \
srcs/c_create.c \
srcs/c_create2.c

NAME = miniRT

MLX = ./minilib_metal/Makefile

CC = gcc

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I ./includes/*

all : $(NAME)

$(NAME) : $(OBJ)
	$(MLX) all
	$(CC) $(CFLAGS) $(OBJ) 

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all