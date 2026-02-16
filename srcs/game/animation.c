/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:42:25 by selevray          #+#    #+#             */
/*   Updated: 2026/02/16 09:58:53 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    *get_player_sprite(t_game *game)
{
    void **sprites;

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

