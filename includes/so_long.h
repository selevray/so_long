/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:10:00 by selevray          #+#    #+#             */
/*   Updated: 2026/02/23 11:49:57 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* Keyboard keys */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_SPACE 32

/* Tile */
# define TILE_SIZE 64
# define MAGENTA 0x00FF00FF

/* Map elements */
# define WALL '1'
# define EMPTY '0'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

/* Events */
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17

/* Player directions */
# define DIR_UP 0
# define DIR_DOWN 1
# define DIR_LEFT 2
# define DIR_RIGHT 3

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}					t_list;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_enemy
{
	int				x;
	int				y;
	int				direction;
}					t_enemy;

typedef struct s_bullet
{
	int				x;
	int				y;
	int				direction;
	int				active;
}					t_bullet;

typedef struct s_textures
{
	void			*floor_top_left;
	void			*floor_top_center;
	void			*floor_top_right;
	void			*floor_left;
	void			*floor_right;
	void			*floor_bottom_left;
	void			*floor_bottom_center;
	void			*floor_bottom_right;
	void			*floor;
	void			*water1;
	void			*water2;
	void			*tree;
	void			*collectible[6];
	void			*exit;
	void			*player_up[4];
	void			*player_down[4];
	void			*player_left[4];
	void			*player_right[4];
	void			*enemy[4];
	void			*bullet;
	void			*youwin;
	void			*gameover;
}					t_textures;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	void			*img_buffer;
	char			*img_data;
	int				img_bpp;
	int				img_line_len;
	int				img_endian;
	char			**map;
	int				map_width;
	int				map_height;
	t_textures		textures;
	int				player_x;
	int				player_y;
	int				player_direction;
	int				anim_frame;
	int				moves;
	int				collectibles_left;
	int				game_won;
	int				tile_size;
	int				collectible_anim_frame;
	int				enemy_anim_frame;
	int				key_up;
	int				key_left;
	int				key_down;
	int				key_right;
	struct timeval	last_anim_time;
	t_enemy			*enemies;
	int				enemy_count;
	int				enemy_timer;
	t_bullet		bullets[10];
	int				bullet_count;
	int				game_ended;
}					t_game;

typedef struct s_water_neighbors
{
	int				top;
	int				bottom;
	int				left;
	int				right;
}					t_water_neighbors;

typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;

// ========== PARSING ==========

// parsing/parse_map.c
char				**parse_map(char *filename);
char				**list_to_array(t_list *head, int count_line);

// parsing/validation.c
int					is_map_size_valid(t_game *game);
int					is_rectangular(char **map, int nb_lines);
int					is_wall_line(char *line);
int					is_surrounded_by_walls(char **map, int nb_lines);

// parsing/validation_elements.c
int					has_valid_chars(char **map, int nb_lines);
int					has_valid_elements(char **map, int nb_lines);
int					count_char(char **map, int nb_lines, char c);

// parsing/flood_fill.c
int					is_path_valid(char **map, int nb_lines);
void				flood_fill(char **map, int x, int y);
int					check_all_accessible(char **map_copy, int nb_lines);

// parsing/map_utils.c
t_list				*build_list(int fd, int *count);
char				**copy_map(char **map, int nb_lines);
void				find_player_position(char **map, int nb_lines, int *x,
						int *y);

// ========== UTILS ==========

// utils/get_next_line.c
char				*get_next_line(int fd);

// utils/str_base.c
size_t				ft_strlen(const char *str);
char				*ft_strchr(const char *string, int searchedChar);
char				*ft_strdup(const char *src);
void				*ft_memcpy(void *dest, const void *src, size_t n);

// utils/str_utils.c
char				*ft_strtrim(char *str, char *charset);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);

// utils/utils.c
char				*ft_itoa(int n);
void				*ft_memset(void *s, int c, size_t n);

// utils/list_utils.c
void				add_bottom(t_list **head, t_list *new);
void				free_list(t_list *head);

// ========== GAME ==========

// game/init_game.c
int					init_game(t_game *game, char **map, int nb_lines);

// game/init_entities.c
void				init_all_textures_null(t_game *game);
void				init_enemies(t_game *game, char **map, int nb_lines);

// game/init_textures.c
void				init_player_textures_null(t_game *game);
void				init_collectible_textures_null(t_game *game);
void				init_enemy_textures_null(t_game *game);
void				init_floor_textures_null(t_game *game);
void				init_other_textures_null(t_game *game);

// game/control.c
int					handle_keypress(int keycode, t_game *game);
int					close_game(void *param);

// game/control_action.c
void				toggle_anim(t_game *game);
void				check_enemy_collision(t_game *game, int nx, int ny);
void				handle_tile_effects(t_game *game, int nx, int ny);

// game/enemy_move.c
void				move_enemies(t_game *game);
void				remove_enemy(t_game *game, int index);

// game/bullet_move.c
void				move_bullets(t_game *game);

// game/gameloop.c
int					game_loop(t_game *game);
void				*get_player_sprite(t_game *game);

// game/render.c
void				render_map(t_game *game);
void				render_tile(t_game *game, int x, int y);

// game/render_floor.c
char				get_tile_type(t_game *game, int x, int y);
void				*get_floor_texture(t_game *game, int x, int y);

// game/render_trans.c
void				put_image_with_transparency(t_game *game, void *floor,
						void *sprite, t_pos pos);

// game/render_utils.c
void				put_image_to_buffer(t_game *game, void *img, int x, int y);
void				render_bullets_on_tile(t_game *game, int x, int y);
void				shoot_bullet(t_game *game);
void				display_move_counter(t_game *game);
void				write_moves_console(t_game *game);
void				display_win_message(t_game *game);

// game/cleanup.c
void				cleanup_game(t_game *game);
void				cleanup_textures(t_game *game);
void				cleanup_enemy_textures(t_game *game);
void				cleanup_floor_textures(t_game *game);
void				cleanup_other_textures(t_game *game);

// game/cleanup_helper.c
void				cleanup_map(char **map);
void				cleanup_enemies(t_game *game);
void				cleanup_mlx(t_game *game);
void				cleanup_player_textures(t_game *game);
void				cleanup_collectible_textures(t_game *game);

// ========== GRAPHICS ==========

// graphics/load_textures_all.c
void				*load_texture(void *mlx, char *path);
int					load_all_textures(t_game *game);

// graphics/load_textures_floor.c
int					load_water_textures(t_game *game);
int					load_floor_bottom_textures(t_game *game);
int					load_floor_top_textures(t_game *game);
int					load_floor_texture(t_game *game);

// graphics/load_textures_hero.c
int					load_hero_down(t_game *game);
int					load_hero_up(t_game *game);
int					load_hero_left(t_game *game);
int					load_hero_right(t_game *game);

// graphics/load_textures_other.c
int					load_other_texture(t_game *game);
int					load_collectible(t_game *game);
int					load_enemy(t_game *game);

#endif
