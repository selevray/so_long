/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_other.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:53:05 by selevray          #+#    #+#             */
/*   Updated: 2026/02/11 12:59:48 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_other_texture(t_game *game)
{
	game->textures.collectible = load_texture(game->mlx,
			"texture/other/milk_small.xpm");
	if (!game->textures.collectible)
		return (0);
	game->textures.exit = load_texture(game->mlx, "texture/other/exit.xpm");
	if (!game->textures.exit)
		return (0);
	game->textures.enemy = load_texture(game->mlx, "texture/other/enemy.xpm");
	if (!game->textures.enemy)
		return (0);
	game->textures.tree = load_texture(game->mlx, "texture/other/tree.xpm");
	if (!game->textures.tree)
		return (0);
	return (1);
}