/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:24:06 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:43:27 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	update_anim_frame(t_game *game, struct timeval *current)
{
	long	elapsed_ms;

	elapsed_ms = (current->tv_sec - game->last_anim_time.tv_sec) * 1000
		+ (current->tv_usec - game->last_anim_time.tv_usec) / 1000;
	if (elapsed_ms < 150)
		return (0);
	game->collectible_anim_frame++;
	if (game->collectible_anim_frame >= 6)
		game->collectible_anim_frame = 0;
	game->last_anim_time = *current;
	return (1);
}

static int	update_bullets(t_game *game)
{
	static int	bullet_timer = 0;

	bullet_timer++;
	if (bullet_timer >= 1000)
	{
		move_bullets(game);
		bullet_timer = 0;
		return (1);
	}
	return (0);
}

int	game_loop(t_game *game)
{
	struct timeval	current_time;
	int				need_render;

	if (game->game_ended)
		return (0);
	need_render = 0;
	gettimeofday(&current_time, NULL);
	need_render += update_anim_frame(game, &current_time);
	need_render += update_bullets(game);
	if (need_render)
		render_map(game);
	return (0);
}

void	*get_player_sprite(t_game *game)
{
	void	**sprites;

	if (game->player_direction == 0)
		sprites = game->textures.player_up;
	else if (game->player_direction == 1)
		sprites = game->textures.player_down;
	else if (game->player_direction == 2)
		sprites = game->textures.player_left;
	else
		sprites = game->textures.player_right;
	return (sprites[game->anim_frame]);
}
