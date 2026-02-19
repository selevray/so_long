/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:42:28 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:43:45 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_bullet_step(t_game *game, int i)
{
	if (game->bullets[i].direction == 0)
		game->bullets[i].y--;
	else if (game->bullets[i].direction == 1)
		game->bullets[i].y++;
	else if (game->bullets[i].direction == 2)
		game->bullets[i].x--;
	else if (game->bullets[i].direction == 3)
		game->bullets[i].x++;
}

static void	check_bullet_enemies(t_game *game, int i)
{
	char	tile;
	int		j;

	tile = get_tile_type(game, game->bullets[i].x, game->bullets[i].y);
	if (tile == 'W' || tile == 'T')
		game->bullets[i].active = 0;
	j = 0;
	while (j < game->enemy_count)
	{
		if (game->bullets[i].x == game->enemies[j].x
			&& game->bullets[i].y == game->enemies[j].y)
		{
			game->bullets[i].active = 0;
			remove_enemy(game, j);
			break ;
		}
		j++;
	}
}

void	move_bullets(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (game->bullets[i].active)
		{
			move_bullet_step(game, i);
			check_bullet_enemies(game, i);
		}
		i++;
	}
}
