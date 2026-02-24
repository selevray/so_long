# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selevray <selevray@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 14:42:25 by selevray          #+#    #+#              #
#    Updated: 2026/02/19 12:28:08 by selevray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = so_long
BONUS_NAME  = so_long_bonus
CC          = cc
CFLAGS      = -Wall -g3 -Wextra -Werror

# ---- Mandatory paths ----
SRCDIR      = srcs
OBJDIR      = objs
INCDIR      = includes
MLX_PATH    = ./minilibx-linux
MLX_LIB     = $(MLX_PATH)/libmlx.a
MLX_FLAGS   = -L$(MLX_PATH) -lmlx -lm -lXext -lX11

# ---- Bonus paths ----
BNS_DIR     = bonus
BNS_SRCDIR  = $(BNS_DIR)/srcs
BNS_OBJDIR  = $(BNS_DIR)/objs
BNS_INCDIR  = $(BNS_DIR)/includes
BNS_MLX     = $(BNS_DIR)/minilibx-linux
BNS_MLX_LIB = $(BNS_MLX)/libmlx.a
BNS_FLAGS   = -L$(BNS_MLX) -lmlx -lm -lXext -lX11

# ---- Source files (relative to srcs/) ----
SRCS =	main.c \
		parsing/parse_map.c \
		parsing/validation.c \
		parsing/validation_elements.c \
		parsing/flood_fill.c \
		parsing/map_utils.c \
		game/init_game.c \
		game/init_entities.c \
		game/init_textures.c \
		game/control.c \
		game/control_action.c \
		game/enemy_move.c \
		game/bullet_move.c \
		game/gameloop.c \
		game/render.c \
		game/render_floor.c \
		game/render_trans.c \
		game/render_utils.c \
		game/cleanup.c \
		game/cleanup_helper.c \
		graphics/load_textures_all.c \
		graphics/load_textures_floor.c \
		graphics/load_textures_hero.c \
		graphics/load_textures_other.c \
		utils/get_next_line.c \
		utils/list_utils.c \
		utils/str_base.c \
		utils/str_utils.c \
		utils/utils.c

OBJS     = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
BNS_OBJS = $(addprefix $(BNS_OBJDIR)/, $(SRCS:.c=.o))

HEADERS     = $(INCDIR)/so_long.h
BNS_HEADERS = $(BNS_INCDIR)/so_long.h

# ============================================================

all: $(NAME)

# ---- Mandatory ----

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MLX_PATH) -c $< -o $@

# ---- Bonus ----

bonus: $(BONUS_NAME)

$(BNS_MLX_LIB):
	$(MAKE) -C $(BNS_MLX)

$(BONUS_NAME): $(BNS_MLX_LIB) $(BNS_OBJS)
	$(CC) $(CFLAGS) $(BNS_OBJS) $(BNS_MLX_LIB) $(BNS_FLAGS) -o $(BONUS_NAME)

$(BNS_OBJDIR)/%.o: $(BNS_SRCDIR)/%.c $(BNS_HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(BNS_INCDIR) -I$(BNS_MLX) -c $< -o $@

# ---- Standard rules ----

clean:
	rm -rf $(OBJDIR) $(BNS_OBJDIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
