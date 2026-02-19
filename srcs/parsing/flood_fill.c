/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:17:01 by selevray          #+#    #+#             */
/*   Updated: 2026/02/09 21:38:58 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x, y - 1);
	flood_fill(map, x, y + 1);
	flood_fill(map, x - 1, y);
	flood_fill(map, x + 1, y);
}

int	check_all_accessible(char **map_copy, int nb_lines)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == 'C' || map_copy[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_path_valid(char **map, int nb_lines)
{
	int x;
	int y;
	char **map_copy;
	int result;
	int i;
	find_player_position(map, nb_lines, &x, &y);
	map_copy = copy_map(map, nb_lines);
	flood_fill(map_copy, x, y);
	result = check_all_accessible(map_copy, nb_lines);
	i = 0;
	while (i < nb_lines)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (result);
}