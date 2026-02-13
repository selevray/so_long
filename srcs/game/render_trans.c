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

static void	copy_image_data(char *dst, char *src, int size_line, int bpp)
{
	int	i;
	int	j;
	int	pixel_offset;
	int	color;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			pixel_offset = i * size_line + j * (bpp / 8);
			color = *(int *)(src + pixel_offset);
			*(int *)(dst + pixel_offset) = color;
			j++;
		}
		i++;
	}
}

static void	overlay_sprite(char *dst, char *sprite_data, int size_line, int bpp)
{
	int	i;
	int	j;
	int	pixel_offset;
	int	color;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			pixel_offset = i * size_line + j * (bpp / 8);
			color = *(int *)(sprite_data + pixel_offset);
			if ((color & 0x00FFFFFF) != MAGENTA)
				*(int *)(dst + pixel_offset) = color;
			j++;
		}
		i++;
	}
}

void	put_image_with_transparency(t_game *game, void *floor, void *sprite,
		int x, int y)
{
	void *composite;
	char *comp_data;
	char *floor_data;
	char *sprite_data;
	int bpp;
	int size_line;
	int endian;

	composite = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!composite)
		return ;

	comp_data = mlx_get_data_addr(composite, &bpp, &size_line, &endian);
	floor_data = mlx_get_data_addr(floor, &bpp, &size_line, &endian);
	sprite_data = mlx_get_data_addr(sprite, &bpp, &size_line, &endian);

	copy_image_data(comp_data, floor_data, size_line, bpp);

	overlay_sprite(comp_data, sprite_data, size_line, bpp);

	mlx_put_image_to_window(game->mlx, game->window, composite, x, y);

	mlx_destroy_image(game->mlx, composite);
}