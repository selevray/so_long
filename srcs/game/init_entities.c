/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:44:37 by selevray          #+#    #+#             */
/*   Updated: 2026/02/24 11:55:49 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill_enemies(t_game *game, char **map, int nb_lines)
{
	int	i;
	int	j;
	int	index;

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

void	init_enemies(t_game *game, char **map, int nb_lines)
{
	game->enemy_count = count_char(map, nb_lines, 'X');
	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		return ;
	fill_enemies(game, map, nb_lines);
}

void	init_all_textures_null(t_game *game)
{
	init_player_textures_null(game);
	init_collectible_textures_null(game);
	init_enemy_textures_null(game);
	init_floor_textures_null(game);
	init_other_textures_null(game);
}
