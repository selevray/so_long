# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selevray <selevray@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 14:42:25 by selevray          #+#    #+#              #
#    Updated: 2026/02/19 11:51:12 by selevray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = so_long
BONUS_NAME  = so_long_bonus
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror

# ---- Mandatory paths ----
MAN_DIR     = mandatory
MAN_SRCDIR  = $(MAN_DIR)/srcs
MAN_OBJDIR  = $(MAN_DIR)/objs
MAN_INC     = $(MAN_DIR)/includes
MAN_MLX     = $(MAN_DIR)/minilibx-linux
MAN_MLX_LIB = $(MAN_MLX)/libmlx.a

# ---- Bonus paths ----
BNS_DIR     = bonus
BNS_SRCDIR  = $(BNS_DIR)/srcs
BNS_OBJDIR  = $(BNS_DIR)/objs
BNS_INC     = $(BNS_DIR)/includes
BNS_MLX     = $(BNS_DIR)/minilibx-linux
BNS_MLX_LIB = $(BNS_MLX)/libmlx.a

# ---- MLX link flags ----
MLX_FLAGS   = -lmlx -lm -lXext -lX11

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

MAN_OBJS = $(addprefix $(MAN_OBJDIR)/, $(SRCS:.c=.o))
BNS_OBJS = $(addprefix $(BNS_OBJDIR)/, $(SRCS:.c=.o))

# ============================================================
# ---- Rules ----
# ============================================================

all: $(NAME)

# ---- Mandatory ----

$(MAN_MLX_LIB):
	$(MAKE) -C $(MAN_MLX)

$(NAME): $(MAN_MLX_LIB) $(MAN_OBJS)
	$(CC) $(CFLAGS) $(MAN_OBJS) -L$(MAN_MLX) $(MLX_FLAGS) -o $(NAME)

$(MAN_OBJDIR)/%.o: $(MAN_SRCDIR)/%.c $(MAN_INC)/so_long.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MAN_INC) -I$(MAN_MLX) -c $< -o $@

# ---- Bonus ----

bonus: $(BONUS_NAME)

$(BNS_MLX_LIB):
	$(MAKE) -C $(BNS_MLX)

$(BONUS_NAME): $(BNS_MLX_LIB) $(BNS_OBJS)
	$(CC) $(CFLAGS) $(BNS_OBJS) -L$(BNS_MLX) $(MLX_FLAGS) -o $(BONUS_NAME)

$(BNS_OBJDIR)/%.o: $(BNS_SRCDIR)/%.c $(BNS_INC)/so_long.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(BNS_INC) -I$(BNS_MLX) -c $< -o $@

# ---- Standard rules ----

clean:
	rm -rf $(MAN_OBJDIR) $(BNS_OBJDIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
