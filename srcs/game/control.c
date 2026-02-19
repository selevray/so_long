/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:53:07 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 10:59:55 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	handle_special_keys(int keycode, t_game *game)
{
	if (keycode == KEY_SPACE)
	{
		shoot_bullet(game);
		return (1);
	}
	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	return (0);
}

static int	apply_movement(int keycode, t_game *game, int *nx, int *ny)
{
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		game->player_direction = 0;
		(*ny)--;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		game->player_direction = 1;
		(*ny)++;
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		game->player_direction = 2;
		(*nx)--;
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		game->player_direction = 3;
		(*nx)++;
	}
	else
		return (0);
	return (1);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	nx;
	int	ny;

	if (handle_special_keys(keycode, game))
		return (0);
	nx = game->player_x;
	ny = game->player_y;
	if (!apply_movement(keycode, game, &nx, &ny))
		return (0);
	if (get_tile_type(game, nx, ny) == 'W'
		|| get_tile_type(game, nx, ny) == 'T')
		return (0);
	game->player_x = nx;
	game->player_y = ny;
	game->moves++;
	toggle_anim(game);
	move_enemies(game);
	check_enemy_collision(game, nx, ny);
	handle_tile_effects(game, nx, ny);
	render_map(game);
	return (0);
}

int	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup_game(game);
	exit(0);
}
