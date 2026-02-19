/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:04:36 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 09:53:00 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player_textures_null(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures.player_up[i] = NULL;
		game->textures.player_down[i] = NULL;
		game->textures.player_left[i] = NULL;
		game->textures.player_right[i] = NULL;
		i++;
	}
}

void	init_collectible_textures_null(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		game->textures.collectible[i] = NULL;
		i++;
	}
}

void	init_enemy_textures_null(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures.enemy[i] = NULL;
		i++;
	}
}

void	init_floor_textures_null(t_game *game)
{
	game->textures.floor = NULL;
	game->textures.floor_top_left = NULL;
	game->textures.floor_top_center = NULL;
	game->textures.floor_top_right = NULL;
	game->textures.floor_bottom_left = NULL;
	game->textures.floor_bottom_center = NULL;
	game->textures.floor_bottom_right = NULL;
	game->textures.floor_left = NULL;
	game->textures.floor_right = NULL;
}

void	init_other_textures_null(t_game *game)
{
	game->textures.water1 = NULL;
	game->textures.water2 = NULL;
	game->textures.tree = NULL;
	game->textures.exit = NULL;
	game->textures.bullet = NULL;
	game->textures.youwin = NULL;
	game->textures.gameover = NULL;
}