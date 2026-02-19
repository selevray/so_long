/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:47:24 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:43:05 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image_to_buffer(t_game *game, void *img, int x, int y)
{
	t_img	src;
	int		i;
	int		j;

	if (!img)
		return ;
	src.addr = mlx_get_data_addr(img, &src.bpp, &src.line_len, &src.endian);
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (x + j >= 0 && x + j < game->map_width * TILE_SIZE && y + i >= 0
				&& y + i < game->map_height * TILE_SIZE)
			{
				*(unsigned int *)(game->img_data + ((y + i)
							* game->img_line_len) + ((x + j) * (game->img_bpp
								/ 8))) = *(unsigned int *)(src.addr + (i
							* src.line_len) + (j * (src.bpp / 8)));
			}
			j++;
		}
		i++;
	}
}

void	display_move_counter(t_game *game)
{
	char	*moves_str;
	char	*temp;
	int		i;

	i = game->moves;
	temp = ft_itoa(i);
	if (!temp)
		return ;
	moves_str = ft_strjoin("Mouvements: ", temp);
	free(temp);
	if (!moves_str)
		return ;
	mlx_string_put(game->mlx, game->window, 10, 20, 0xFFFFFF, moves_str);
	free(moves_str);
}

void	render_bullets_on_tile(t_game *game, int x, int y)
{
	int		i;
	void	*floor;
	t_pos	pos;

	floor = get_floor_texture(game, x, y);
	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	i = 0;
	while (i < 10)
	{
		if (game->bullets[i].active && x == game->bullets[i].x
			&& y == game->bullets[i].y)
			put_image_with_transparency(game, floor,
				game->textures.bullet, pos);
		i++;
	}
}

void	shoot_bullet(t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (game->bullets[i].active == 0)
		{
			game->bullets[i].x = game->player_x;
			game->bullets[i].y = game->player_y;
			game->bullets[i].direction = game->player_direction;
			game->bullets[i].active = 1;
			return ;
		}
		i++;
	}
}
