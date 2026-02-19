/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:25:31 by selevray          #+#    #+#             */
/*   Updated: 2026/02/18 15:26:39 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	cleanup_enemies(t_game *game)
{
	if (game->enemies)
	{
		free(game->enemies);
		game->enemies = NULL;
	}
}

void	cleanup_mlx(t_game *game)
{
	if (game->img_buffer && game->mlx)
		mlx_destroy_image(game->mlx, game->img_buffer);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	cleanup_player_textures(t_game *game)
{
	int	i;

	if (!game || !game->mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures.player_up[i])
			mlx_destroy_image(game->mlx, game->textures.player_up[i]);
		if (game->textures.player_down[i])
			mlx_destroy_image(game->mlx, game->textures.player_down[i]);
		if (game->textures.player_left[i])
			mlx_destroy_image(game->mlx, game->textures.player_left[i]);
		if (game->textures.player_right[i])
			mlx_destroy_image(game->mlx, game->textures.player_right[i]);
		i++;
	}
}

void	cleanup_collectible_textures(t_game *game)
{
	int i;

	if (!game || !game->mlx)
		return ;
	i = 0;
	while (i < 6)
	{
		if (game->textures.collectible[i])
			mlx_destroy_image(game->mlx, game->textures.collectible[i]);
		i++;
	}
}
