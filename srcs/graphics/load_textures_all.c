/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:20:29 by selevray          #+#    #+#             */
/*   Updated: 2026/02/16 11:52:29 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*load_texture(void *mlx, char *path)
{
	int		widht;
	int		height;
	void	*texture;

	texture = mlx_xpm_file_to_image(mlx, path, &widht, &height);
	if (!texture)
	{
		write(2, "Error\nFailed to load texture: ", 31);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
	return (texture);
}

int	load_all_textures(t_game *game)
{
	if (!load_water_textures(game))
		return (0);
	if (!load_floor_bottom_textures(game))
		return (0);
	if (!load_floor_top_textures(game))
		return (0);
	if (!load_floor_texture(game))
		return (0);
	if (!load_hero_down(game))
		return (0);
	if (!load_hero_left(game))
		return (0);
	if (!load_hero_right(game))
		return (0);
	if (!load_hero_up(game))
		return (0);
	if (!load_other_texture(game))
		return (0);
	if (!load_collectible(game))
		return (0);
	if (!load_enemy(game))
		return (0);
	return (1);
}
