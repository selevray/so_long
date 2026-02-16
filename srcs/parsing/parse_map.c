/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:32:48 by selevray          #+#    #+#             */
/*   Updated: 2026/02/10 17:38:33 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**list_to_array(t_list *head, int count_line)
{
	char **map;
	int i;
	t_list *temp;

	map = malloc(sizeof(char *) * (count_line + 1));
	if (map == NULL)
		return (NULL);
	temp = head;
	i = 0;
	while (temp != NULL)
	{
		map[i] = temp->line;
		temp = temp->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	**parse_map(char *file_name)
{
	t_list	*head;
	char	*line;
	int		fd;
	int		count_line;
	t_list	*new;
	char	**map;
    char    *trimmed;

	head = NULL;
	fd = open(file_name, O_RDONLY);
	count_line = 0;
	while ((line = get_next_line(fd)))
	{
		new = malloc(sizeof(t_list));
		if (new == NULL)
			return (NULL);
        trimmed = ft_strtrim(line, "\n");
        free(line);
		new->line = trimmed;
		new->next = NULL;
		add_bottom(&head, new);
		count_line++;
	}
	close(fd);
	map = list_to_array(head, count_line);
	free_list(head);
	return (map);
}
