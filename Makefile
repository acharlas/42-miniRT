# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 14:13:00 by acharlas          #+#    #+#              #
#    Updated: 2020/11/08 14:13:02 by acharlas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

OS = $(shell uname)

SRC = src/main.c \
	  src/render.c \
	  src/cast_ray.c \
	  src/scene_intersect.c \
	  src/normal.c \
	  src/fct_annext.c \
	  src/ray_intersect.c \
	  src/error_handling.c \
	  src/rotation.c \
	  src/rt_functions.c \
	  src/bmp.c \
	  src/keybind.c \
	  src/color.c \
	  src/sphere.c \
	  src/square.c \
	  src/cylinder.c \
	  src/plane.c \
	  src/triangle.c \
	  src/light.c \
	  src/scene.c \
	  src/camera.c \
	  src/ft_simple_atof.c

CC = clang

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

INC = includes


LDFLAGS = -L libs/minilibx-linux -L libs/libft
LDLIBS = -lmlx -lft -lXext -lX11 -lm
OFLAGS = $(CFLAGS_L) -O2 -flto -funroll-loops -ftree-vectorize

CFLAGS = -Wall -Wextra -I include -isystem libs

ifeq ($(MAKECMDGOALS),debug)
CFLAGS += -g3 -O0
endif

ifeq ($(MAKECMDGOALS),sanitize)
CFLAGS += -g3 -O0 -Wuninitialized 
LDFLAGS += -fsanitize=address -fsanitize=undefined
endif


all : $(NAME)

.PHONY : libft minilibx

libft :
	$(MAKE) -C libs/libft bonus

minilibx :
ifeq ($(OS),Linux)
	$(MAKE) -C libs/minilibx-linux
else
	$(MAKE) -C libs/mlx_metal
endif

$(NAME) : libft minilibx $(OBJ)
ifeq ($(OS),Linux)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)
else
	$(CC) -o $(NAME) $(SRC) $(CFLAGS_M)
	install_name_tool -change libmlx.dylib libs/mlx_metal/libmlx.dylib miniRT
endif

debug : libft minilibx $(OBJ)
ifeq ($(OS),Linux)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)
else
	$(CC) -o $(NAME) $(SRC) $(DFLAGS_M) -O0
	install_name_tool -change libmlx.dylib libs/mlx_metal/libmlx.dylib miniRT
endif

sanitize : libft minilibx $(OBJ)
ifeq ($(OS),Linux)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)
else
	$(CC) -o $(NAME) $(SRC) $(DFLAGS_M) -O0
	install_name_tool -change libmlx.dylib libs/mlx_metal/libmlx.dylib miniRT
endif

opti : libft minilibx
	$(CC) -o $(NAME) $(SRC) $(OFLAGS)

clean :
	rm -f $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C libs/libft $@
	$(MAKE) -C libs/minilibx-linux $@

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME)-debug
	rm -f $(NAME)-opti
	rm -rf *.dSYM
	rm -rf *.bmp
	$(MAKE) -C libs/libft $@

re : fclean all
