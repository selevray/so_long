/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:09:04 by selevray          #+#    #+#             */
/*   Updated: 2026/02/13 12:55:29 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;
	int		nb_lines;
	t_game	game;

	nb_lines = 0;
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./so_long <map.ber>\n", 33);
		return (1);
	}
	map = parse_map(argv[1]);
	if (!map)
	{
		write(2, "Error\nMap parsing failed\n", 25);
		return (1);
	}
	nb_lines = 0;
	while (map[nb_lines])
		nb_lines++;
	if (!init_game(&game, map, nb_lines))
	{
		write(2, "Error\nGame init failed\n", 23);
		return (1);
	}
	if (!is_rectangular(map, nb_lines))
	{
		write(2, "Error\nMap is not rectangular\n", 29);
		return (1);
	}
	if (!is_surrounded_by_walls(map, nb_lines))
	{
		write(2, "Error\nMap not surrounded by walls\n", 35);
		return (1);
	}
	if (!has_valid_elements(map, nb_lines))
	{
		write(2, "Error\nInvalid map elements\n", 27);
		return (1);
	}
	if (!is_path_valid(map, nb_lines))
	{
		write(2, "Error\nNo valid path\n", 20);
		return (1);
	}
	if (!load_all_textures(&game))
	{
		write(2, "Error\nTextures failed\n", 22);
		return (1);
	}
	render_map(&game);
	mlx_hook(game.window, 17, 0, close_game, &game);
	mlx_hook(game.window, 2, 1L << 0, handle_keypress, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
