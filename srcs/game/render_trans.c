/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_trans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:41:09 by selevray          #+#    #+#             */
/*   Updated: 2026/02/13 11:54:53 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image_with_transparency(t_game *game, void *floor, void *sprite,
		int x, int y)
{
	char	*floor_data;
	char	*sprite_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		i;
	int		j;
	int		color;
	int		pixel_offset;

	floor_data = mlx_get_data_addr(floor, &bpp, &size_line, &endian);
	sprite_data = mlx_get_data_addr(sprite, &bpp, &size_line, &endian);
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			pixel_offset = i * size_line + j * (bpp / 8);
			color = *(int *)(sprite_data + pixel_offset);
			if ((color & 0x00FFFFFF) != MAGENTA)
				*(unsigned int *)(game->img_data + ((y + i) * game->img_line_len)
					+ ((x + j) * (game->img_bpp / 8))) = color;
			else
				*(unsigned int *)(game->img_data + ((y + i) * game->img_line_len)
					+ ((x + j) * (game->img_bpp / 8))) =
					*(int *)(floor_data + pixel_offset);
			j++;
		}
		i++;
	}
}