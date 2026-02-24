/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:32:48 by selevray          #+#    #+#             */
/*   Updated: 2026/02/24 12:06:19 by selevray         ###   ########.fr       */
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
		&& file_name[len - 2] == 'e' && file_name[len - 1] == 'r'
		&& file_name[len - 5] != '/')
		return (1);
	return (0);
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
		write(2, "The file extension must be .ber\n", 33);
		return (NULL);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		write(2, "Unable to open the file\n", 24);
		return (NULL);
	}
	count_line = 0;
	head = build_list(fd, &count_line);
	close(fd);
	map = list_to_array(head, count_line);
	free_list(head);
	return (map);
}
