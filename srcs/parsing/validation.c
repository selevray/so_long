/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:33:44 by selevray          #+#    #+#             */
/*   Updated: 2026/02/18 13:45:16 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_map_size_valid(t_game *game)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	if (game->map_width * TILE_SIZE > screen_width)
	{
		write(2, "Error\nMap too wide for screen\n", 31);
		return (0);
	}
	if (game->map_height * TILE_SIZE > screen_height)
	{
		write(2, "Error\nMap too tall for screen\n", 31);
		return (0);
	}
	return (1);
}

int	is_rectangular(char **map, int nb_lines)
{
	size_t	first_len;
	int		i;

	if (map == NULL || nb_lines == 0)
		return (0);
	first_len = ft_strlen(map[0]);
	i = 1;
	while (i < nb_lines)
	{
		if (ft_strlen(map[i]) != first_len)
			return (0);
		i++;
	}
	return (1);
}

int	is_wall_line(char *line)
{
	while (*line)
	{
		if (*line != '1')
			return (0);
		line++;
	}
	return (1);
}

int	is_surrounded_by_walls(char **map, int nb_lines)
{
	size_t width;
	int i;

	width = ft_strlen(map[0]);
	if (!is_wall_line(map[0]) || !is_wall_line(map[nb_lines - 1]))
		return (0);
	i = 1;
	while (i < nb_lines)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
