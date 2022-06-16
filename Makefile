NAME = cub3D
NAME_BONUS = duckling3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

DEBUG =
ifdef DEBUG
CFLAGS += -fsanitize=address
endif

SRC_DIR = $(shell find srcs -type d)

OBJ_DIR = objs
OBJ_DIR_BONUS = objs_bonus
INC_DIR = ./includes/
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux

LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext

INC = -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

PARSING_FILES = parsing.c parser_struct.c parse_map_content.c init_config.c
INIT_FILES = init_structs.c init_mlx.c init_pj.c
ROUTINE_FILES = mlx_routine.c routine_manager.c
ENGINE_FILES = raycasting.c key_events.c simulation_end.c
DRAW_TOOLS = draw_pxl.c draw_circle.c draw_square.c draw_line.c

ROUTINE_BONUS_FILES = mlx_routine_bonus.c routine_manager_bonus.c
EVENT_BONUS_FILES = mouse_events_bonus.c
MINIMAP_BONUS_FILES = minimap_bonus.c minimap_pj_bonus.c

SRC = main.c \
	$(PARSING_FILES) \
	$(INIT_FILES) \
	$(ENGINE_FILES) \
	$(ROUTINE_FILES) \
	$(DRAW_TOOLS)

SRC_BONUS = main_bonus.c \
	$(PARSING_FILES) \
	$(INIT_FILES) \
	$(ENGINE_FILES) \
	$(ROUTINE_BONUS_FILES) \
	$(EVENT_BONUS_FILES) \
	$(DRAW_TOOLS) \
	$(MINIMAP_BONUS_FILES)

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS)/,$(SRC_BONUS:.c=.o))

all: $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(NAME)

bonus: $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(NAME_BONUS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR) all

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR) all

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o:%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

re: fclean all

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

cleanall: fclean
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

.PHONY: fclean clean re all