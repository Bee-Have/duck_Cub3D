# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 12:02:21 by user42            #+#    #+#              #
#    Updated: 2021/04/20 12:06:56 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D
SRCS = 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar rc $@ $^

clean:
		rm -f *.o


fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY : clean fclean re all