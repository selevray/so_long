/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:42:25 by selevray          #+#    #+#             */
/*   Updated: 2026/02/13 15:42:45 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long"

void    *get_player_sprite(t_game *game)
{
    void **sprites;

    if (game->player_direction == 0)
        sprite = game->textures.player_up;
    else if (game->player_direction == 1)
        sprite = game->textures.player_down;
    else if (game->player_direction == 2)
        sprite = game->textures.player_left;
    else if (game->player_direction == 3)
        sprite = game->textures.player_right;
    return (sprites[game->anim_frame]);
}

