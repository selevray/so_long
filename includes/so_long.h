/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:10:00 by selevray          #+#    #+#             */
/*   Updated: 2026/02/11 12:44:26 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

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

/* Tile size */
# define TILE_SIZE 64
# define MAGENTA 0x00FF00FF
# define TILE_SIZE_COLLECTIBLE 32

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

// Directions du joueur
# define DIR_UP 0
# define DIR_DOWN 1
# define DIR_LEFT 2
# define DIR_RIGHT 3

# define MAGENTA 0x00FF00FF

typedef struct s_gnl
{
	char			*str_static;
	char			*buffer;
	char			*temp;
	int				bytes_read;
	int				fd;
}					t_gnl;

/* Structures */
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

typedef struct s_player
{
	int				x;
	int				y;
}					t_player;

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
	void			*collectible;
	void			*exit;

	void			*player_up[4];
	void			*player_down[4];
	void			*player_left[4];
	void			*player_right[4];

	void			*enemy;
}					t_textures;

typedef struct s_game
{
	void			*mlx;
	void			*window;
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
}					t_game;

typedef struct s_water_neighbors
{
	int				top;
	int				bottom;
	int				left;
	int				right;
}					t_water_neighbors;

// ========== PARSING ==========

// parsing/parse_map.c
char				**parse_map(char *filename);
char				**list_to_array(t_list *head, int count_line);

// parsing/validation.c
int					is_rectangular(char **map, int nb_lines);
int					is_wall_line(char *line);
int					is_surrounded_by_walls(char **map, int nb_lines);

// parsing/validation_elements.c
int					has_valid_elements(char **map, int nb_lines);
int					count_char(char **map, int nb_lines, char c);

// parsing/flood_fill.c
int					is_path_valid(char **map, int nb_lines);
void				flood_fill(char **map, int x, int y);
int					check_all_accessible(char **map_copy, int nb_lines);

// parsing/map_utils.c
char				**copy_map(char **map, int nb_lines);
void				find_player_position(char **map, int nb_lines, int *x,
						int *y);

// parsing/utils.c
char				*ft_strtrim(char *str, char *charset);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *string, int searchedChar);
char				*ft_strdup(const char *src);

char				*get_next_line(int fd);

// ========== UTILS ==========

// utils/list_utils.c
void				add_bottom(t_list **head, t_list *new);
void				free_list(t_list *head);

// ========== GAME ==========

// game/init_game.c
int					init_game(t_game *game, char **map, int nb_lines);
void				render_map(t_game *game);
void				put_image_with_transparency(t_game *game, void *floor,
						void *sprite, int x, int y);

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

#endif
