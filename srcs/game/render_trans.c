/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_trans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:41:09 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:44:33 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	write_dst_pixel(t_game *game, int x, int y, unsigned int color)
{
	*(unsigned int *)(game->img_data + (y * game->img_line_len) + (x
				* (game->img_bpp / 8))) = color;
}

void	put_image_with_transparency(t_game *game, void *floor, void *sprite,
		t_pos pos)
{
	t_img	fl;
	t_img	spr;
	int		i;
	int		j;
	int		off;

	fl.addr = mlx_get_data_addr(floor, &fl.bpp, &fl.line_len, &fl.endian);
	spr.addr = mlx_get_data_addr(sprite, &spr.bpp, &spr.line_len, &spr.endian);
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			off = i * spr.line_len + j * (spr.bpp / 8);
			if ((*(int *)(spr.addr + off) & 0x00FFFFFF) != MAGENTA)
				write_dst_pixel(game, pos.x + j, pos.y + i,
					*(int *)(spr.addr + off));
			else
				write_dst_pixel(game, pos.x + j, pos.y + i,
					*(int *)(fl.addr + off));
			j++;
		}
		i++;
	}
}
