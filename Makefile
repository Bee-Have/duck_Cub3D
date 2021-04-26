CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D
SRCS = init_parsing.c list_managment.c parsing_map.c \
		parsing_res_color_rextures.c main.c \
OBJS = $(SRCS:.c=.o)
LIB_DIR = libraries/libft/ \
			libraries/ft_get_file/ \
			libraries/minilibx-linux/
LIBS = libft.a libgetfile.a libmlx.a
LIB_FLAGS = -L$(LIB_DIR) -l$(LIB_DIR) -lm

all: install $(NAME)

$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -03 -c $< -o $@

install:
		cd $(LIB_DIR) && $(MAKE) all
		#$(CC) -L$(LIB_DIR) -l$(LIB) -lm

$(NAME): $(OBJS)
		cp $(LIBS) $(NAME)
		$(CC) $(CFLAGS) $@ $^ $(LIBS)

clean:
		rm -f *.o
		cd $(LIB_DIR) && $(MAKE) clean

fclean: clean
		rm -f $(NAME)
		cd $(LIB_DIR) && $(MAKE) fclean

re: fclean all

.PHONY : clean fclean re all