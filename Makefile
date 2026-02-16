# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selevray <selevray@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 14:42:25 by selevray          #+#    #+#              #
#    Updated: 2026/02/16 13:01:06 by selevray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = so_long
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
INCLUDES    = -I./includes

SRCDIR      = srcs
OBJDIR      = objs
INCDIR      = includes
BNSDIR 		= bonus
MLX_PATH    = ./minilibx-linux
MLX_LIB     = $(MLX_PATH)/libmlx.a
MLX_FLAGS   = -L$(MLX_PATH) -lmlx -lm -lXext -lX11


# Main
MAIN = main.c

# Parsing
PARSING = parsing/parse_map.c \
          parsing/validation.c \
          parsing/validation_elements.c \
          parsing/flood_fill.c \
          parsing/map_utils.c \
          parsing/utils.c

# Game
GAME = game/init_game.c \
	   game/animation.c \
       game/render.c \
	   game/render_trans.c \
	   game/control.c \
	   game/cleanup.c \

# Graphics
GRAPHICS = graphics/load_textures_all.c \
           graphics/load_textures_floor.c \
           graphics/load_textures_hero.c \
           graphics/load_textures_other.c \

# Utils
UTILS = utils/get_next_line.c \
        utils/list_utils.c \
        utils/utils.c

SRC_FILES = $(MAIN) $(PARSING) $(GAME) $(GRAPHICS) $(UTILS)

OBJS        = $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))

HEADERS     = $(INCDIR)/so_long.h \

all: $(NAME)

$(MLX_LIB):
	@echo "Compilation de la MiniLibX..."
	$(MAKE) -C $(MLX_PATH)

$(NAME): $(OBJS) $(MLX_LIB)
	@echo "Création de l'exécutable $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) compilé avec succès !"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_PATH) $(INCLUDES) -c $< -o $@

clean:
	@echo "Nettoyage des objets..."
	rm -rf $(OBJDIR)
	-make -C $(MLX_PATH) clean

fclean: clean
	@echo "Suppression de l'exécutable..."
	rm -f $(NAME)
	-make -C $(MLX_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus