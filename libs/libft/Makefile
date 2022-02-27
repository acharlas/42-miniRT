# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 14:06:54 by acharlas          #+#    #+#              #
#    Updated: 2020/11/08 14:06:57 by acharlas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_strjoin.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line.c

SRC_BONUS = ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstsize_bonus.c \
	ft_lst_remove_if.c \
	ft_lst_to_stra.c \
	ft_stralen.c \
	ft_straclear.c \
	field.c \
	flags.c \
	length.c \
	ft_printf.c \
	ft_fdprintf.c \
	ft_asprintf.c \
	precision.c \
	prefix.c \
	struct.c \
	ft_itoa_base.c \
	ft_printf_utils.c \
	ft_printf_utils2.c \
	arg.c \
	arg2.c \
	ft_is_in_stra.c \
	ft_is_floatstr.c \
	ft_is_digitstr.c \
	ft_strcmp.c


HEADER = libft.h

CC = clang

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g3 -O0

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)

bonus : all $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

clean :
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
