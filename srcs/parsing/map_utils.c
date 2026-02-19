/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:38:32 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:38:32 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player_position(char **map, int nb_lines, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

char	**copy_map(char **map, int nb_lines)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * nb_lines);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < nb_lines)
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	return (copy);
}
