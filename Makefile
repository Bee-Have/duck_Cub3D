CC = gcc
CFLAGS = -fsanitize=address -g3
NAME = cub3D
LIBFT_DIR = libraries/libft
GETFILE_DIR = libraries/ft_get_file
MINILIB_DIR = libraries/minilibx-linux
OPENGL = -lm -lbsd  -lX11 -lXext
LIBS = -L$(LIBFT_DIR) -lft -L$(GETFILE_DIR) -lgetfile \
		-L$(MINILIB_DIR) -lmlx -L$(MINILIB_DIR) -lmlx_Linux
INCLUDES = -Iincludes/ -I$(LIBFT_DIR) -I$(GETFILE_DIR) -I$(MINILIB_DIR)
SRCS = init_parsing.c list_managment.c parsing_map.c \
		parsing_res_colors_textures.c main.c error_managment.c \
		minilibx_managment.c debug.c
OBJS = $(SRCS:.c=.o)

all: install $(NAME)

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
		$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(INCLUDES) $(OPENGL)

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