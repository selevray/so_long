/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:35:27 by selevray          #+#    #+#             */
/*   Updated: 2026/02/10 19:31:15 by selevray         ###   ########.fr       */
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

static void	render_floor(t_game *game, void *texture, int px, int py, int x,
		int y)
{
	mlx_put_image_to_window(game->mlx, game->window, get_floor_texture(game, x,
			y), px, py);
	mlx_put_image_to_window(game->mlx, game->window, texture, px, py);
}

void	render_tile(t_game *game, int x, int y)
{
	int		pixel_x;
	int		pixel_y;
	char	type;

	pixel_x = x * TILE_SIZE;
	pixel_y = y * TILE_SIZE;
	type = get_tile_type(game, x, y);
	if (type == 'W')
		mlx_put_image_to_window(game->mlx, game->window, game->textures.water1,
			pixel_x, pixel_y);
	else if (type == 'P')
		render_floor(game, game->textures.player_down[0], pixel_x, pixel_y, x, y);
	else if (type == 'T')
		render_floor(game, game->textures.tree, pixel_x, pixel_y, x, y);
	else if (type == 'C')
		render_floor(game, game->textures.collectible, pixel_x, pixel_y, x, y);
	else if (type == 'E')
		render_floor(game, game->textures.exit, pixel_x, pixel_y, x, y);
	else if (type == '0')
	{
		mlx_put_image_to_window(game->mlx, game->window, get_floor_texture(game,
				x, y), pixel_x, pixel_y);
	}
}

void	render_map(t_game *game)
{
	int y;
    int x;

    y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
}