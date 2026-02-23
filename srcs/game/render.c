/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:35:27 by selevray          #+#    #+#             */
/*   Updated: 2026/02/23 10:23:35 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_floor(t_game *game, void *texture, int x, int y)
{
	void	*floor;
	t_pos	pos;

	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	floor = get_floor_texture(game, x, y);
	put_image_with_transparency(game, floor, texture, pos);
}

static void	render_tile_type(t_game *game, char type, int x, int y)
{
	int		px;
	int		py;

	px = x * TILE_SIZE;
	py = y * TILE_SIZE;
	if (type == 'W')
		put_image_to_buffer(game, game->textures.water1, px, py);
	if (type == '0' || type == 'P' || type == 'X')
		put_image_to_buffer(game, get_floor_texture(game, x, y), px, py);
	if (type == 'T')
		render_floor(game, game->textures.tree, x, y);
	if (type == 'C')
		render_floor(game,
			game->textures.collectible[game->collectible_anim_frame % 6],
			x, y);
	if (type == 'E')
		render_floor(game, game->textures.exit, x, y);
}

static void	render_enemies_on_tile(t_game *game, int x, int y)
{
	int		i;
	void	*floor;
	t_pos	pos;

	floor = get_floor_texture(game, x, y);
	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	i = 0;
	while (i < game->enemy_count)
	{
		if (x == game->enemies[i].x && y == game->enemies[i].y)
			put_image_with_transparency(game, floor,
				game->textures.enemy[game->enemies[i].direction], pos);
		i++;
	}
}

void	render_tile(t_game *game, int x, int y)
{
	char	type;
	t_pos	pos;

	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	type = get_tile_type(game, x, y);
	render_tile_type(game, type, x, y);
	render_enemies_on_tile(game, x, y);
	if (x == game->player_x && y == game->player_y)
		put_image_with_transparency(game, get_floor_texture(game, x, y),
			get_player_sprite(game), pos);
	render_bullets_on_tile(game, x, y);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

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
	mlx_put_image_to_window(game->mlx, game->window, game->img_buffer, 0, 0);
	display_move_counter(game);
}
