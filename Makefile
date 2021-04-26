CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D
SRCS = init_parsing.c list_managment.c parsing_map.c \
		parsing_res_colors_textures main.c
OBJS = $(SRCS:.c=.o)
#LIB_DIR = libraries/libft/ \
			libraries/ft_get_file/ \
			libraries/minilibx-linux/
LIBS_TEST = -I ./libraries/libft/ -L ./libraries/libft/\
			-I ./libraries/ft_get_file/ -L ./libraries/ft_get_file/ \
			-I ./libraries/minilibx-linux/ -L ./libraries/minilibx-linux/
LIBS = -L ./libraries/libft -lft -L ./libraries/ft_get_file -lgetfile
LIB_MLX = -L ./libraries/minilibx-linux -lmlx -lm -Imlx_linux -lXext -lX11 -lm

all: install $(NAME)

$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -c $< -o $@

install:
		cd libraries/libft/ && $(MAKE) all
		cd libraries/ft_get_file/ && $(MAKE) all
		cd libraries/minilibx-linux/ && $(MAKE) all

$(NAME): $(OBJS)
		cp libraries/libft/libft.a $(NAME)
		cp libraries/ft_get_file/libgetfile.a $(NAME)
		cp libraries/minilibx-linux/libmlx.a $(NAME)
		echo "bonjour"
		$(CC) $(CFLAGS) ${LIBS_TEST}  $^ -o $@

clean:
		rm -f *.o
		cd libraries/libft/ && $(MAKE) clean
		cd libraries/ft_get_file/ && $(MAKE) clean
		cd libraries/minilibx-linux/ && $(MAKE) clean

fclean: clean
		rm -f $(NAME)
		cd libraries/libft/ && $(MAKE) fclean
		cd libraries/ft_get_file/ && $(MAKE) fclean

re: fclean all

.PHONY : clean fclean re all install