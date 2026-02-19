/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:49:32 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 10:51:00 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	get_tile_type(t_game *game, int x, int y)
{
	if (game->map[y][x] != '1')
		return (game->map[y][x]);
	if (y == 0 || y == game->map_height - 1 || x == 0 || x == game->map_width
		- 1)
		return ('W');
	else if (game->map[y - 1][x] != '1' || game->map[y + 1][x] != '1'
		|| game->map[y][x - 1] != '1' || game->map[y][x + 1] != '1')
		return ('T');
	return ('W');
}

t_water_neighbors	check_water_neighbors(t_game *game, int x, int y)
{
	t_water_neighbors	water;

	water.top = 0;
	water.bottom = 0;
	water.left = 0;
	water.right = 0;
	if (get_tile_type(game, x, y - 1) == 'W')
		water.top = 1;
	if (get_tile_type(game, x, y + 1) == 'W')
		water.bottom = 1;
	if (get_tile_type(game, x - 1, y) == 'W')
		water.left = 1;
	if (get_tile_type(game, x + 1, y) == 'W')
		water.right = 1;
	return (water);
}

void	*select_floor_texture(t_game *game, t_water_neighbors water)
{
	if (water.top && water.left)
		return (game->textures.floor_top_left);
	else if (water.top && water.right)
		return (game->textures.floor_top_right);
	else if (water.bottom && water.left)
		return (game->textures.floor_bottom_left);
	else if (water.bottom && water.right)
		return (game->textures.floor_bottom_right);
	else if (water.top)
		return (game->textures.floor_top_center);
	else if (water.bottom)
		return (game->textures.floor_bottom_center);
	else if (water.left)
		return (game->textures.floor_left);
	else if (water.right)
		return (game->textures.floor_right);
	return (game->textures.floor);
}

void	*get_floor_texture(t_game *game, int x, int y)
{
	t_water_neighbors	water;

	water = check_water_neighbors(game, x, y);
	return (select_floor_texture(game, water));
}
