NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = $(shell find srcs -type d)

OBJ_DIR = objs
INC_DIR = ./includes/
LIBFT_DIR = ./libft_duck
GNL_DIR = ./Lib_get_file
MLX_DIR = ./minilibx-linux

LIBS = -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgetfile -L$(MLX_DIR) -lmlx -lm -lbsd -lx11 -lXext

INC = -I$(LIBFT_DIR)/Includes -I$(GNL_DIR)/Includes -I$(MLX_DIR) -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

SRC = 

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

.PHONY: fclean clean re all