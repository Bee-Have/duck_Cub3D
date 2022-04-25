NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

DEBUG =
ifdef DEBUG
CFLAGS += -fsanitize=address
endif

SRC_DIR = $(shell find srcs -type d)

OBJ_DIR = objs
INC_DIR = ./includes/
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext

INC = -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

SRC = main_test.c

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(NAME)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR) all

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
	rm -f $(NAME)

cleanall: fclean
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

.PHONY: fclean clean re all