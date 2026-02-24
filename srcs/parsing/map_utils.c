/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:38:32 by selevray          #+#    #+#             */
/*   Updated: 2026/02/23 15:16:06 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_list_full(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
}

static int	add_line_to_list(t_list **head, char *line, int *count)
{
	t_list	*new;
	char	*trimmed;

	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(line);
		free_list_full(*head);
		return (-1);
	}
	trimmed = ft_strtrim(line, "\n");
	free(line);
	if (trimmed == NULL)
	{
		free(new);
		free_list_full(*head);
		return (-1);
	}
	new->line = trimmed;
	new->next = NULL;
	add_bottom(head, new);
	(*count)++;
	return (0);
}

t_list	*build_list(int fd, int *count)
{
	t_list	*head;
	char	*line;

	head = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (add_line_to_list(&head, line, count) == -1)
			return (NULL);
		line = get_next_line(fd);
	}
	return (head);
}

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
			if (map[i][j] == PLAYER)
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
