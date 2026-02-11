/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:33:44 by selevray          #+#    #+#             */
/*   Updated: 2026/02/09 21:34:00 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	size_t	width;
	int		i;

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