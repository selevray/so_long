/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:38:43 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 10:39:53 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	toggle_anim(t_game *game)
{
	if (game->anim_frame == 2)
		game->anim_frame = 3;
	else
		game->anim_frame = 2;
}

void	check_enemy_collision(t_game *game, int nx, int ny)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (nx == game->enemies[i].x && ny == game->enemies[i].y)
		{
			game->game_ended = 1;
			display_win_message(game);
			render_map(game);
			usleep(3000000);
			cleanup_game(game);
			exit(0);
		}
		i++;
	}
}

void	handle_tile_effects(t_game *game, int nx, int ny)
{
	if (game->map[ny][nx] == COLLECTIBLE)
	{
		game->collectibles_left--;
		game->map[ny][nx] = EMPTY;
	}
	if (game->map[ny][nx] == EXIT && game->collectibles_left == 0)
	{
		game->game_ended = 1;
		render_map(game);
		display_win_message(game);
		usleep(3000000);
		cleanup_game(game);
		exit(0);
	}
}
