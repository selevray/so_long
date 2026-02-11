/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:41:18 by selevray          #+#    #+#             */
/*   Updated: 2026/02/11 11:46:58 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_game(t_game *game, char **map, int nb_lines)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (0);
	game->map = map;
	game->map_height = nb_lines;
	game->map_width = ft_strlen(map[0]);
	win_width = game->map_width * TILE_SIZE;
	win_height = game->map_height * TILE_SIZE;
	game->window = mlx_new_window(game->mlx, win_width, win_height,
			"Cat SIMULATOR");
	if (game->window == NULL)
		return (0);
	find_player_position(map, nb_lines, &game->player_x, &game->player_y);
	game->collectibles_left = count_char(map, nb_lines, COLLECTIBLE);
	game->moves = 0;
	game->game_won = 0;
	return (1);
}
