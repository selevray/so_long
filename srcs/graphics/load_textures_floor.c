/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:11:23 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 13:21:28 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_water_textures(t_game *game)
{
	game->textures.water1 = load_texture(game->mlx, "texture/floor/water1.xpm");
	if (!game->textures.water1)
		return (0);
	game->textures.water2 = load_texture(game->mlx, "texture/floor/water2.xpm");
	if (!game->textures.water2)
		return (0);
	return (1);
}

int	load_floor_bottom_textures(t_game *game)
{
	game->textures.floor = load_texture(game->mlx, "texture/floor/floor.xpm");
	if (!game->textures.floor)
		return (0);
	game->textures.floor_bottom_center = load_texture(game->mlx,
			"texture/floor/floor_bottom_center.xpm");
	if (!game->textures.floor_bottom_center)
		return (0);
	game->textures.floor_bottom_left = load_texture(game->mlx,
			"texture/floor/floor_bottom_left.xpm");
	if (!game->textures.floor_bottom_left)
		return (0);
	game->textures.floor_bottom_right = load_texture(game->mlx,
			"texture/floor/floor_bottom_right.xpm");
	if (!game->textures.floor_bottom_right)
		return (0);
	return (1);
}

int	load_floor_top_textures(t_game *game)
{
	game->textures.floor_top_center = load_texture(game->mlx,
			"texture/floor/floor_top_center.xpm");
	if (!game->textures.floor_top_center)
		return (0);
	game->textures.floor_top_left = load_texture(game->mlx,
			"texture/floor/floor_top_left.xpm");
	if (!game->textures.floor_top_left)
		return (0);
	game->textures.floor_top_right = load_texture(game->mlx,
			"texture/floor/floor_top_right.xpm");
	if (!game->textures.floor_top_right)
		return (0);
	return (1);
}

int	load_floor_texture(t_game *game)
{
	game->textures.floor_left = load_texture(game->mlx,
			"texture/floor/floor_left.xpm");
	if (!game->textures.floor_left)
		return (0);
	game->textures.floor_right = load_texture(game->mlx,
			"texture/floor/floor_right.xpm");
	if (!game->textures.floor_right)
		return (0);
	return (1);
}
