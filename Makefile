NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = $(shell find srcs -type d)

OBJ_DIR = objs
INC_DIR = ./includes/
LIBFT_DIR = ./libft_duck
GNL_DIR = ./Lib_get_file
MLX_DIR = ./minilibx-linux

LIBS = -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgetfile -L$(MLX_DIR) -lmlx -lm -lbsd -lXext

INC = -I$(LIBFT_DIR)/Includes -I$(GNL_DIR)/Includes -I$(MLX_DIR) -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

SRC = main_test.c

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(LIBFT_DIR)/libft.a $(GNL_DIR)/libgetfile.a $(MLX_DIR)/libmlx.a $(NAME)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR) all

$(GNL_DIR)/libgetfile.a:
	make -C $(GNL_DIR) all

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR) all

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

cleanall: fclean
	make -C $(LIBFT_DIR) fclean
	make -C $(GNL_DIR) fclean
	make -C $(MLX_DIR) clean

.PHONY: fclean clean re all