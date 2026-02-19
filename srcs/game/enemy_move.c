/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:38:00 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:43:53 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_enemy_dir(t_game *game, int i, int *nx, int *ny)
{
	*nx = game->enemies[i].x;
	*ny = game->enemies[i].y;
	if (game->player_x > game->enemies[i].x)
	{
		(*nx)++;
		game->enemies[i].direction = 2;
	}
	else if (game->player_x < game->enemies[i].x)
	{
		(*nx)--;
		game->enemies[i].direction = 3;
	}
	else if (game->player_y > game->enemies[i].y)
	{
		(*ny)++;
		game->enemies[i].direction = 0;
	}
	else if (game->player_y < game->enemies[i].y)
	{
		(*ny)--;
		game->enemies[i].direction = 1;
	}
}

static void	apply_enemy_move(t_game *game, int i, int new_x, int new_y)
{
	char	tile;

	tile = get_tile_type(game, new_x, new_y);
	if (tile != 'W' && tile != 'T' && tile != 'E' && tile != 'X' && tile != 'C')
	{
		game->map[game->enemies[i].y][game->enemies[i].x] = '0';
		game->enemies[i].x = new_x;
		game->enemies[i].y = new_y;
		game->map[new_y][new_x] = 'X';
	}
}

void	remove_enemy(t_game *game, int index)
{
	int	i;

	printf("Ennemi %d supprimé!\n", index);
	i = index;
	while (i < game->enemy_count - 1)
	{
		game->enemies[i] = game->enemies[i + 1];
		i++;
	}
	game->enemy_count--;
}

void	move_enemies(t_game *game)
{
	int	i;
	int	new_x;
	int	new_y;

	i = 0;
	while (i < game->enemy_count)
	{
		update_enemy_dir(game, i, &new_x, &new_y);
		apply_enemy_move(game, i, new_x, new_y);
		i++;
	}
}
