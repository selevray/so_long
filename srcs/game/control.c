/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:53:07 by selevray          #+#    #+#             */
/*   Updated: 2026/02/13 13:19:42 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		game->player_direction = 0;
		new_y--;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		game->player_direction = 1;
		new_y++;
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		game->player_direction = 2;
		new_x--;
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		game->player_direction = 3;
		new_x++;
	}
	else if (keycode == KEY_SPACE)
	{
		printf("TIR! Direction actuelle: %d\n", game->player_direction);
			// ← Ajouter
		shoot_bullet(game);
		render_map(game);
		return (0);
	}
	else if (keycode == KEY_ESC)
		exit(0);
	else
		return (0);
	tile = get_tile_type(game, new_x, new_y);
	if (tile == 'W' || tile == 'T')
		return (0);
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	move_enemies(game);
	printf("Mouvements : %d\n", game->moves);
	if (game->map[new_y][new_x] == 'X')
	{
		render_map(game);
		exit(0);
	}
	if (game->map[new_y][new_x] == COLLECTIBLE)
	{
		game->collectibles_left--;
		game->map[new_y][new_x] = EMPTY;
	}
	if (game->map[new_y][new_x] == EXIT && game->collectibles_left == 0)
	{
		exit(0);
	}
	render_map(game);
	return (0);
}

void	move_enemies(t_game *game)
{
	int		i;
	int		new_x;
	int		new_y;
	char	tile;

	i = 0;
	while (i < game->enemy_count)
	{
		new_x = game->enemies[i].x;
		new_y = game->enemies[i].y;
		if (game->player_x > game->enemies[i].x)
			new_x++;
		else if (game->player_x < game->enemies[i].x)
			new_x--;
		if (game->player_y > game->enemies[i].y)
			new_y++;
		else if (game->player_y < game->enemies[i].y)
			new_y--;
		tile = get_tile_type(game, new_x, new_y);
		if (tile != 'W' && tile != 'T' && tile != 'E')
		{
			game->map[game->enemies[i].y][game->enemies[i].x] = '0';
			game->enemies[i].x = new_x;
			game->enemies[i].y = new_y;
			game->map[new_y][new_x] = 'X';
		}
		i++;
	}
}

void	move_bullets(t_game *game)
{
	int		i;
	int		j;
	char	tile;

	i = 0;
	j = 0;
	while (i < 10)
	{
		if (game->bullets[i].active)
		{
			if (game->bullets[i].direction == 0)
				game->bullets[i].y--;
			else if (game->bullets[i].direction == 1)
				game->bullets[i].y++;
			else if (game->bullets[i].direction == 2)
				game->bullets[i].x--;
			else if (game->bullets[i].direction == 3)
				game->bullets[i].x++;
			tile = get_tile_type(game, game->bullets[i].x, game->bullets[i].y);
			if (tile == 'W' || tile == 'T')
			{
				game->bullets[i].active = 0;
			}
			j = 0;
			while (j < game->enemy_count)
			{
				if (game->bullets[i].x == game->enemies[j].x
					&& game->bullets[i].y == game->enemies[j].y)
				{
					printf("ENNEMI TOUCHÉ!\n");
					game->bullets[i].active = 0;
					remove_enemy(game, j);
					break ;
				}
				j++;
			}
		}
		i++;
	}
}

int	game_loop(t_game *game)
{
	static int	bullet_timer = 0;

	bullet_timer++;
	if (bullet_timer >= 70)
	{
		move_bullets(game);
		bullet_timer = 0;
		render_map(game);
	}
	return (0);
}

void	remove_enemy(t_game *game, int index)
{
	int	i;

	printf("Ennemi %d supprimé!\n", index);
	i = index;
	while (i < game->enemy_count - 1)
	{
		game->enemies[i] = game->enemies[i + 1];
		i++;
	}
	game->enemy_count--;
}

int	close_game(void *param)
{
	(void)param;
	exit(0);
	return (0);
}
