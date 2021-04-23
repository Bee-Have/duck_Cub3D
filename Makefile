# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 12:02:21 by user42            #+#    #+#              #
#    Updated: 2021/04/23 15:53:39 by amarini-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D
SRCS = init_parsing.c list_managment.c parsing_map.c \
		parsing_res_color_rextures.c main.c \
OBJS = $(SRCS:.c=.o)
LIB_DIR = libraries/libft libraries/ft_get_files

all: $(NAME)

$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -03 -c $< -o $@

$(NAME): $(OBJS)
		ar rc $@ $^

clean:
		rm -f *.o


fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY : clean fclean re all