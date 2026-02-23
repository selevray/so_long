/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:09:04 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 10:59:02 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	error_exit(t_game *game, char *msg, int len)
{
	if (msg)
		write(2, msg, len);
	cleanup_game(game);
	return (0);
}

static char	**setup_map(t_game *game, char *filename, int *nb_lines)
{
	char	**map;

	map = parse_map(filename);
	if (!map)
	{
		error_exit(game, "Error\nMap parsing failed\n", 25);
		return (NULL);
	}
	while (map[*nb_lines])
		(*nb_lines)++;
	if (*nb_lines == 0)
	{
		cleanup_map(map);
		error_exit(game, "Error\nEmpty map\n", 14);
		return (NULL);
	}
	if (!init_game(game, map, *nb_lines))
	{
		error_exit(game, "Error\nGame init failed\n", 23);
		return (NULL);
	}
	return (map);
}

static int	validate_map(t_game *game, char **map, int nb_lines)
{
	if (!is_map_size_valid(game))
		return (error_exit(game, NULL, 0));
	if (!is_rectangular(map, nb_lines))
		return (error_exit(game, "Error\nMap is not rectangular\n", 29));
	if (!is_surrounded_by_walls(map, nb_lines))
		return (error_exit(game, "Error\nMap not surrounded by walls\n", 35));
	if (!has_valid_elements(map, nb_lines))
		return (error_exit(game, "Error\nInvalid map elements\n", 27));
	if (!is_path_valid(map, nb_lines))
		return (error_exit(game, "Error\nNo valid path\n", 20));
	return (1);
}

static int	run_game(t_game *game)
{
	if (!load_all_textures(game))
		return (error_exit(game, "Error\nTextures failed\n", 22));
	render_map(game);
	mlx_hook(game->window, 17, 0, close_game, game);
	mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	char	**map;
	int		nb_lines;
	t_game	game = {0};

	nb_lines = 0;
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./so_long <map.ber>\n", 33);
		return (1);
	}
	map = setup_map(&game, argv[1], &nb_lines);
	if (!map)
		return (1);
	if (!validate_map(&game, map, nb_lines))
		return (1);
	return (!run_game(&game));
}
