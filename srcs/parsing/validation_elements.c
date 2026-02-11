/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:36:58 by selevray          #+#    #+#             */
/*   Updated: 2026/02/10 17:39:41 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_char(char **map, int nb_lines, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
    count = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
int	has_valid_elements(char **map, int nb_lines)
{
	int	count_p;
	int	count_e;
	int	count_c;

	count_p = count_char(map, nb_lines, 'P');
	count_e = count_char(map, nb_lines, 'E');
	count_c = count_char(map, nb_lines, 'C');
	if (count_p != 1 || count_e != 1 || count_c < 1)
		return (0);
	return (1);
}
