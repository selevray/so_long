/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_hero.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:35:25 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:45:15 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_hero_down(t_game *game)
{
	game->textures.player_down[0] = load_texture(game->mlx,
			"texture/player/front_milka.xpm");
	if (!game->textures.player_down[0])
		return (0);
	game->textures.player_down[1] = load_texture(game->mlx,
			"texture/player/front1_milka.xpm");
	if (!game->textures.player_down[1])
		return (0);
	game->textures.player_down[2] = load_texture(game->mlx,
			"texture/player/front2_milka.xpm");
	if (!game->textures.player_down[2])
		return (0);
	game->textures.player_down[3] = load_texture(game->mlx,
			"texture/player/front3_milka.xpm");
	if (!game->textures.player_down[3])
		return (0);
	return (1);
}

int	load_hero_up(t_game *game)
{
	game->textures.player_up[0] = load_texture(game->mlx,
			"texture/player/back_milka.xpm");
	if (!game->textures.player_up[0])
		return (0);
	game->textures.player_up[1] = load_texture(game->mlx,
			"texture/player/back1_milka.xpm");
	if (!game->textures.player_up[1])
		return (0);
	game->textures.player_up[2] = load_texture(game->mlx,
			"texture/player/back2_milka.xpm");
	if (!game->textures.player_up[2])
		return (0);
	game->textures.player_up[3] = load_texture(game->mlx,
			"texture/player/back3_milka.xpm");
	if (!game->textures.player_up[3])
		return (0);
	return (1);
}

int	load_hero_left(t_game *game)
{
	game->textures.player_left[0] = load_texture(game->mlx,
			"texture/player/left_milka.xpm");
	if (!game->textures.player_left[0])
		return (0);
	game->textures.player_left[1] = load_texture(game->mlx,
			"texture/player/left1_milka.xpm");
	if (!game->textures.player_left[1])
		return (0);
	game->textures.player_left[2] = load_texture(game->mlx,
			"texture/player/left2_milka.xpm");
	if (!game->textures.player_left[2])
		return (0);
	game->textures.player_left[3] = load_texture(game->mlx,
			"texture/player/left3_milka.xpm");
	if (!game->textures.player_left[3])
		return (0);
	return (1);
}

int	load_hero_right(t_game *game)
{
	game->textures.player_right[0] = load_texture(game->mlx,
			"texture/player/right_milka.xpm");
	if (!game->textures.player_right[0])
		return (0);
	game->textures.player_right[1] = load_texture(game->mlx,
			"texture/player/right1_milka.xpm");
	if (!game->textures.player_right[1])
		return (0);
	game->textures.player_right[2] = load_texture(game->mlx,
			"texture/player/right2_milka.xpm");
	if (!game->textures.player_right[2])
		return (0);
	game->textures.player_right[3] = load_texture(game->mlx,
			"texture/player/right3_milka.xpm");
	if (!game->textures.player_right[3])
		return (0);
	return (1);
}
