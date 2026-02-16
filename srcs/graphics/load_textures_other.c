/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_other.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:53:05 by selevray          #+#    #+#             */
/*   Updated: 2026/02/16 14:18:03 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_other_texture(t_game *game)
{
	game->textures.exit = load_texture(game->mlx, "texture/other/exit.xpm");
	if (!game->textures.exit)
		return (0);
	game->textures.tree = load_texture(game->mlx, "texture/other/tree.xpm");
	if (!game->textures.tree)
		return (0);
	game->textures.bullet = load_texture(game->mlx, "texture/other/bullet.xpm");
	if (!game->textures.bullet)
		return (0);
	game->textures.youwin = load_texture(game->mlx,
			"texture/other/win.xpm");
	if (!game->textures.youwin)
		return (0);
	game->textures.gameover = load_texture(game->mlx,
			"texture/other/gameover.xpm");
	if (!game->textures.gameover)
		return (0);
	return (1);
}

int	load_collectible(t_game *game)
{
	game->textures.collectible[0] = load_texture(game->mlx,
			"texture/other/front_milka_tablet.xpm");
	if (!game->textures.collectible[0])
		return (0);
	game->textures.collectible[1] = load_texture(game->mlx,
			"texture/other/front5_milka_tablet.xpm");
	if (!game->textures.collectible[1])
		return (0);
	game->textures.collectible[2] = load_texture(game->mlx,
			"texture/other/front2_milka_tablet.xpm");
	if (!game->textures.collectible[2])
		return (0);
	game->textures.collectible[3] = load_texture(game->mlx,
			"texture/other/front4_milka_tablet.xpm");
	if (!game->textures.collectible[3])
		return (0);
	game->textures.collectible[4] = load_texture(game->mlx,
			"texture/other/front5_milka_tablet.xpm");
	if (!game->textures.collectible[4])
		return (0);
	game->textures.collectible[5] = load_texture(game->mlx,
			"texture/other/front1_milka_tablet.xpm");
	if (!game->textures.collectible[5])
		return (0);
	return (1);
}

int	load_enemy(t_game *game)
{
	game->textures.enemy[0] = load_texture(game->mlx,
			"texture/other/front_mm.xpm");
	if (!game->textures.enemy[0])
		return (0);
	game->textures.enemy[1] = load_texture(game->mlx,
			"texture/other/back_mm.xpm");
	if (!game->textures.enemy[1])
		return (0);
	game->textures.enemy[2] = load_texture(game->mlx,
			"texture/other/right_mm.xpm");
	if (!game->textures.enemy[2])
		return (0);
	game->textures.enemy[3] = load_texture(game->mlx,
			"texture/other/left_mm.xpm");
	if (!game->textures.enemy[3])
		return (0);
	return (1);
}
