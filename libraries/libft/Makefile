# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 15:27:38 by amarini-          #+#    #+#              #
#    Updated: 2021/04/23 15:38:43 by amarini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC = ft_atoi.c ft_fill_str.c ft_split.c ft_str_cmp.c ft_str_cmp.c \
		ft_strcpy.c ft_strjoin.c ft_strlen.c ft_strncpy.c ft_strtrim.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $@ $^
		ranlib $(NAME)

re: fclean all

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

.PHONY: all re clean fclean