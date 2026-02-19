/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:32:48 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:41:06 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**list_to_array(t_list *head, int count_line)
{
	char	**map;
	int		i;
	t_list	*temp;

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

static int	check_extension(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 5)
		return (0);
	if (file_name[len - 4] == '.' && file_name[len - 3] == 'b'
		&& file_name[len - 2] == 'e' && file_name[len - 1] == 'r')
		return (1);
	return (0);
}

static t_list	*build_list(int fd, int *count)
{
	t_list	*head;
	char	*line;
	t_list	*new;
	char	*trimmed;

	head = NULL;
	line = get_next_line(fd);
	while (line)
	{
		new = malloc(sizeof(t_list));
		if (new == NULL)
			return (NULL);
		trimmed = ft_strtrim(line, "\n");
		free(line);
		new->line = trimmed;
		new->next = NULL;
		add_bottom(&head, new);
		(*count)++;
		line = get_next_line(fd);
	}
	return (head);
}

char	**parse_map(char *file_name)
{
	t_list	*head;
	int		fd;
	int		count_line;
	char	**map;

	if (!check_extension(file_name))
	{
		write(2, "Error\n", 6);
		write(2, "La map doit avoir l'extension .ber\n", 35);
		return (NULL);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		write(2, "Impossible d'ouvrir le fichier\n", 31);
		return (NULL);
	}
	count_line = 0;
	head = build_list(fd, &count_line);
	close(fd);
	map = list_to_array(head, count_line);
	free_list(head);
	return (map);
}
