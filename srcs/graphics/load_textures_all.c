/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:20:29 by selevray          #+#    #+#             */
/*   Updated: 2026/02/11 09:26:29 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*load_texture(void *mlx, char *path)
{
	int		widht;
	int		height;
	void	*texture;

	texture = mlx_xpm_file_to_image(mlx, path, &widht, &height);
	if (!texture)
	{
		write(2, "Error\nFailed to load texture: ", 31);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
	return (texture);
}

int	load_all_textures(t_game *game)
{
    printf("Loading water textures...\n");
	if (!load_water_textures(game))
		return (printf("FAILED: water textures\n"), 0);
	printf("Loading floor bottom textures...\n");
	if (!load_floor_bottom_textures(game))
		return (printf("FAILED: floor bottom textures\n"), 0);
	printf("Loading floor top textures...\n");
	if (!load_floor_top_textures(game))
		return (printf("FAILED: floor top textures\n"), 0);
	printf("Loading floor texture...\n");
	if (!load_floor_texture(game))
		return (printf("FAILED: floor texture\n"), 0);
	printf("Loading hero down textures...\n");
	if (!load_hero_down(game))
		return (printf("FAILED: hero down textures\n"), 0);
	printf("Loading hero left textures...\n");
	if (!load_hero_left(game))
		return (printf("FAILED: hero left textures\n"), 0);
	printf("Loading hero right textures...\n");
	if (!load_hero_right(game))
		return (printf("FAILED: hero right textures\n"), 0);
	printf("Loading hero up textures...\n");
	if (!load_hero_up(game))
		return (printf("FAILED: hero up textures\n"), 0);
	printf("Loading other textures...\n");
	if (!load_other_texture(game))
		return (printf("FAILED: other textures\n"), 0);
	printf("All textures loaded successfully!\n");
	return (1);
}

void put_image_transparent(t_game *game, void *img, int x, int y)
{
    char    *data;
    int     bpp;
    int     size_line;
    int     endian;
    int     i;
    int     j;
    int     color;
    
    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    
    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            // Récupérer la couleur du pixel
            color = *(int *)(data + (i * size_line + j * (bpp / 8)));
            
            // Si le pixel n'est PAS noir (transparent), on le dessine
            if ((color & 0x00FFFFFF) != 0x00000000)
            {
                mlx_pixel_put(game->mlx, game->window, 
                    x + j, y + i, color);
            }
            j++;
        }
        i++;
    }
}
