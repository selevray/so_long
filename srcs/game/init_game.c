/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:41:18 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:44:05 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	init_mlx(t_game *game, int win_width, int win_height)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (0);
	game->window = mlx_new_window(game->mlx, win_width, win_height, "Cat");
	if (game->window == NULL)
		return (0);
	game->img_buffer = mlx_new_image(game->mlx, win_width, win_height);
	if (game->img_buffer == NULL)
		return (0);
	game->img_data = mlx_get_data_addr(game->img_buffer, &game->img_bpp,
			&game->img_line_len, &game->img_endian);
	return (1);
}

static void	init_game_state(t_game *game, char **map, int nb_lines)
{
	find_player_position(map, nb_lines, &game->player_x, &game->player_y);
	game->collectibles_left = count_char(map, nb_lines, COLLECTIBLE);
	game->moves = 0;
	game->player_direction = 1;
	game->enemy_timer = 0;
	game->game_won = 0;
	game->anim_frame = 0;
	game->collectible_anim_frame = 0;
	game->key_up = 0;
	game->key_left = 0;
	game->key_down = 0;
	game->key_right = 0;
	game->bullet_count = 0;
	game->game_ended = 0;
}

static void	init_bullets(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		game->bullets[i].active = 0;
		i++;
	}
}

int	init_game(t_game *game, char **map, int nb_lines)
{
	int	win_width;
	int	win_height;

	init_all_textures_null(game);
	game->map = map;
	game->map_height = nb_lines;
	game->map_width = ft_strlen(map[0]);
	win_width = game->map_width * TILE_SIZE;
	win_height = game->map_height * TILE_SIZE;
	if (!init_mlx(game, win_width, win_height))
		return (0);
	init_game_state(game, map, nb_lines);
	init_bullets(game);
	init_enemies(game, map, nb_lines);
	gettimeofday(&game->last_anim_time, NULL);
	return (1);
}
