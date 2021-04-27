CC = gcc
CFLAGS = -Wall -Wextra #-Werror
NAME = cub3D
#LIB_DIR = libraries/libft/ \
			libraries/ft_get_file/ \
			libraries/minilibx-linux/
#LIBS_TEST = -I ./libraries/libft/ -L ./libraries/libft/\
			-I ./libraries/ft_get_file/ -L ./libraries/ft_get_file/ \
			-I ./libraries/minilibx-linux/ -L ./libraries/minilibx-linux/
#LIBS = -L ./libraries/libft -lft -L ./libraries/ft_get_file -lgetfile
#LIB_MLX = -L ./libraries/minilibx-linux -lmlx -lm -Imlx_linux -lXext -lX11 -lm
LIBFT_DIR = libraries/libft
GETFILE_DIR = libraries/ft_get_file
MINILIB_DIR = libraries/minilibx-linux
OPENGL = -lm -lbsd  -lX11 -lXext
LIBS = -L$(LIBFT_DIR) -lft -L$(GETFILE_DIR) -lgetfile -L$(MINILIB_DIR) -lmlx
INCLUDES = -Iincludes/ -I$(LIBFT_DIR) -I$(GETFILE_DIR) -I$(MINILIB_DIR)
SRCS = init_parsing.c list_managment.c parsing_map.c \
		parsing_res_colors_textures.c main.c error_managment.c \
		minilibx_managment.c
OBJS = $(SRCS:.c=.o)

all: install $(NAME)

#$(OBJS): $(SRCS)
#		$(CC) $(CFLAGS) $(LIBS) -c $^ -o $@
.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

install:
		cd $(LIBFT_DIR) && $(MAKE) all
		cd $(GETFILE_DIR) && $(MAKE) all
		cd $(MINILIB_DIR) && $(MAKE) all

$(NAME): $(OBJS)
		cp $(LIBFT_DIR)/libft.a $(NAME)
		cp $(GETFILE_DIR)/libgetfile.a $(NAME)
		cp $(MINILIB_DIR)/libmlx.a $(NAME)
		#$(CC) $(CFLAGS) $^ $(INCLUDES) $(OPENGL) $(LIBS) -o $@
		$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(OPENGL) $(LIBS)

#depend: $(SRCS)
#		makedepend $(INCUDES) $^

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