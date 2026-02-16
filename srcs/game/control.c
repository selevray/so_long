/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:53:07 by selevray          #+#    #+#             */
/*   Updated: 2026/02/16 16:55:15 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void display_win_message(t_game *game)
{
    int center_x;
    int center_y;

    printf("DISPLAY WIN MESSAGE appelée!\n");
    printf("Texture youwin: %p\n", game->textures.youwin);

    center_x = (game->map_width * TILE_SIZE) / 2 - 100;
    center_y = (game->map_height * TILE_SIZE) / 2 - 30;

    printf("Position: x=%d, y=%d\n", center_x, center_y);

    put_image_to_buffer(game, game->textures.youwin, center_x, center_y);
    mlx_put_image_to_window(game->mlx, game->window, game->img_buffer, 0, 0);
}

void display_gameover_message(t_game *game)
{
    int center_x;
    int center_y;

    center_x = (game->map_width * TILE_SIZE) / 2 - 100;
    center_y = (game->map_height * TILE_SIZE) / 2 - 30;

    put_image_to_buffer(game, game->textures.gameover, center_x, center_y);
    mlx_put_image_to_window(game->mlx, game->window, game->img_buffer, 0, 0);
}

int	handle_keypress(int keycode, t_game *game)
{
	int		new_x;
	int		new_y;
	char	tile;
	int		i;

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
		shoot_bullet(game);
		return (0);
	}
	else if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	else
		return (0);
	tile = get_tile_type(game, new_x, new_y);
	if (tile == 'W' || tile == 'T')
		return (0);
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	if (game->anim_frame == 2)
		game->anim_frame = 3;
	else if (game->anim_frame == 3)
		game->anim_frame = 2;
	else
		game->anim_frame = 2;
	move_enemies(game);
	i = 0;
	while (i < game->enemy_count)
	{
		if (new_x == game->enemies[i].x && new_y == game->enemies[i].y)
		{
			render_map(game);
			display_gameover_message(game);
			usleep(3000000);
			cleanup_game(game);
			exit(0);
		}
		i++;
	}
	if (game->map[new_y][new_x] == COLLECTIBLE)
	{
		game->collectibles_left--;
		game->map[new_y][new_x] = EMPTY;
	}
	if (game->map[new_y][new_x] == EXIT && game->collectibles_left == 0)
	{
		render_map(game);
		display_win_message(game);
		usleep(3000000);
		cleanup_game(game);
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
		{
			new_x++;
			game->enemies[i].direction = 2;
		}
		else if (game->player_x < game->enemies[i].x)
		{
			new_x--;
			game->enemies[i].direction = 3;
		}
		else if (game->player_y > game->enemies[i].y)
		{
			new_y++;
			game->enemies[i].direction = 0;
		}
		else if (game->player_y < game->enemies[i].y)
		{
			new_y--;
			game->enemies[i].direction = 1;
		}
		tile = get_tile_type(game, new_x, new_y);
		if (tile != 'W' && tile != 'T' && tile != 'E' && tile != 'X')
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

int game_loop(t_game *game)
{
    static int bullet_timer = 0;
    static int collectible_anim_timer = 0;
    int need_render;
    
    need_render = 0;
    
    bullet_timer++;
    if (bullet_timer >= 1)
    {
        move_bullets(game);
        bullet_timer = 0;
        need_render = 1;
    }
    
    collectible_anim_timer++;
    if (collectible_anim_timer >= 5)
    {
        game->collectible_anim_frame++;
        if (game->collectible_anim_frame >= 6)
            game->collectible_anim_frame = 0;
        collectible_anim_timer = 0;
        need_render = 1;
    }
    
    if (need_render)
        render_map(game);
    
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
	t_game	*game;

	game = (t_game *)param;
	cleanup_game(game);
	exit(0);
}
