/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:01:28 by selevray          #+#    #+#             */
/*   Updated: 2026/02/18 15:26:49 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_enemy_textures(t_game *game)
{
	int	i;

	if (!game || !game->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures.enemy[i])
			mlx_destroy_image(game->mlx, game->textures.enemy[i]);
		i++;
	}
}

void	cleanup_floor_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->textures.floor)
		mlx_destroy_image(game->mlx, game->textures.floor);
	if (game->textures.floor_top_left)
		mlx_destroy_image(game->mlx, game->textures.floor_top_left);
	if (game->textures.floor_top_center)
		mlx_destroy_image(game->mlx, game->textures.floor_top_center);
	if (game->textures.floor_top_right)
		mlx_destroy_image(game->mlx, game->textures.floor_top_right);
	if (game->textures.floor_bottom_left)
		mlx_destroy_image(game->mlx, game->textures.floor_bottom_left);
	if (game->textures.floor_bottom_center)
		mlx_destroy_image(game->mlx, game->textures.floor_bottom_center);
	if (game->textures.floor_bottom_right)
		mlx_destroy_image(game->mlx, game->textures.floor_bottom_right);
	if (game->textures.floor_left)
		mlx_destroy_image(game->mlx, game->textures.floor_left);
	if (game->textures.floor_right)
		mlx_destroy_image(game->mlx, game->textures.floor_right);
}

void	cleanup_other_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->textures.water1)
		mlx_destroy_image(game->mlx, game->textures.water1);
	if (game->textures.water2)
		mlx_destroy_image(game->mlx, game->textures.water2);
	if (game->textures.tree)
		mlx_destroy_image(game->mlx, game->textures.tree);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx, game->textures.exit);
	if (game->textures.bullet)
		mlx_destroy_image(game->mlx, game->textures.bullet);
	if (game->textures.youwin)
		mlx_destroy_image(game->mlx, game->textures.youwin);
	if (game->textures.gameover)
		mlx_destroy_image(game->mlx, game->textures.gameover);
}

void	cleanup_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	cleanup_player_textures(game);
	cleanup_collectible_textures(game);
	cleanup_enemy_textures(game);
	cleanup_floor_textures(game);
	cleanup_other_textures(game);
}

void	cleanup_game(t_game *game)
{
	cleanup_textures(game);
	cleanup_map(game->map);
	cleanup_enemies(game);
	cleanup_mlx(game);
}
