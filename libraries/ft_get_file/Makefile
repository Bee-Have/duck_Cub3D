# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 15:34:59 by amarini-          #+#    #+#              #
#    Updated: 2021/04/26 12:11:44 by amarini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libgetfile.a
SRC = ft_get_file.c get_next_line.c get_next_line_utils.c
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