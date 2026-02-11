/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:53:07 by selevray          #+#    #+#             */
/*   Updated: 2026/02/11 14:04:13 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	int new_x;
	int new_y;
	char tile;

	new_x = game->player_x;
	new_y = game->player_y;

	if (keycode == KEY_W || keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		new_x++;
	else if (keycode == KEY_ESC)
		exit(0);
	else
		return (0);

	tile = get_tile_type(game, new_x, new_y);

	if (tile == 'W' || tile == 'T')
		return (0);
    
    game->player_x = new_x;
    game->player_y = new_y;

    render_map(game);
	return (0);
}
