/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:09:04 by selevray          #+#    #+#             */
/*   Updated: 2026/02/10 19:28:24 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	verify_all_textures(t_game *game)
{
	printf("\n=== TEXTURE VERIFICATION ===\n");
	printf("Water: %p %p\n", game->textures.water1, game->textures.water2);
	printf("Floor: %p\n", game->textures.floor);
	printf("Floor top left: %p\n", game->textures.floor_top_left);
	printf("Floor top center: %p\n", game->textures.floor_top_center);
	printf("Floor top right: %p\n", game->textures.floor_top_right);
	printf("Floor bottom left: %p\n", game->textures.floor_bottom_left);
	printf("Floor bottom center: %p\n", game->textures.floor_bottom_center);
	printf("Floor bottom right: %p\n", game->textures.floor_bottom_right);
	printf("Floor left: %p\n", game->textures.floor_left);
	printf("Floor right: %p\n", game->textures.floor_right);
	printf("Tree: %p\n", game->textures.tree);
	printf("Collectible: %p\n", game->textures.collectible);
	printf("Exit: %p\n", game->textures.exit);
	printf("Enemy: %p\n", game->textures.enemy);
	printf("Player down[0]: %p\n", game->textures.player_down[0]);
	printf("Player down[1]: %p\n", game->textures.player_down[1]);
	printf("Player down[2]: %p\n", game->textures.player_down[2]);
	printf("Player down[3]: %p\n", game->textures.player_down[3]);
	printf("===========================\n\n");
}

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
	printf("First line: [%s]\n", map[0]);
	printf("ft_strlen result: %zu\n", ft_strlen(map[0]));
	printf("Real length check:\n");
	for (int i = 0; map[0][i]; i++)
	{
		printf("map[0][%d] = '%c' (ASCII %d)\n", i, map[0][i], map[0][i]);
	}
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
	if (!load_all_textures(&game))
	{
		write(2, "Error\nTextures failed\n", 22);
		return (1);
	}
	verify_all_textures(&game);
	render_map(&game);
	printf("Map width: %d, height: %d\n", game.map_width, game.map_height);
	printf("Window width: %d, height: %d\n", game.map_width * TILE_SIZE,
		game.map_height * TILE_SIZE);
	render_map(&game);
	printf("Entering loop...\n");
	mlx_loop(game.mlx);
	return (0);
}
