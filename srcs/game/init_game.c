/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:41:18 by selevray          #+#    #+#             */
/*   Updated: 2026/02/16 12:36:19 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_enemies(t_game *game, char **map, int nb_lines)
{
	int	i;
	int	j;
	int	index;

	game->enemy_count = count_char(map, nb_lines, 'X');
	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		return ;
	index = 0;
	i = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'X')
			{
				game->enemies[index].x = j;
				game->enemies[index].y = i;
				game->enemies[index].direction = 0;
				index++;
			}
			j++;
		}
		i++;
	}
}

int	init_game(t_game *game, char **map, int nb_lines)
{
	int	win_width;
	int	win_height;
	int	i;

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
	game->img_buffer = mlx_new_image(game->mlx, win_width, win_height);
	if (game->img_buffer == NULL)
		return (0);
	game->img_data = mlx_get_data_addr(game->img_buffer, &game->img_bpp,
			&game->img_line_len, &game->img_endian);
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
	i = 0;
	while (i < 10)
	{
		game->bullets[i].active = 0;
		i++;
	}
	init_enemies(game, map, nb_lines);
	return (1);
}
