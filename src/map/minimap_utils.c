/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/09 19:21:54 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_pixel(t_image *image, int x, int y, unsigned int color)
{
	int	i;
	int	*data;

	data = (int *)(image->pixel_data);
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT && color != 0)
		data[y * SCREEN_WIDTH + x] = color;
}

void	draw_player(t_game *game, t_vector pos, int size, unsigned int color)
{
	t_image		*image;
	t_line		direction;
	t_dvector	p_dir;

	p_dir = game->player.dir;
	image = &game->display.img;
	direction.color = color;
	direction.thickness = 5;
	direction.s = (t_vector){pos.y + size / 2, pos.x + size / 2};
	direction.f = (t_vector){direction.s.y + p_dir.y * size * 2, direction.s.x
		+ p_dir.x * size * 2};
	draw_square(image, pos, size, color);
	draw_line(&direction, image);
}

void	draw_wall(t_image *image, t_vector on_screen_pos, t_vector on_map_pos,
		t_minimap *minimap)
{
	t_vector	pos;

	pos.y = on_screen_pos.y + on_map_pos.y * minimap->scale;
	pos.x = on_screen_pos.x + on_map_pos.x * minimap->scale;
	draw_square(image, pos, minimap->scale, minimap->wall_color);
}

void	draw_floor_mm(t_image *image, t_vector on_screen_pos,
		t_vector on_map_pos, t_minimap *minimap)
{
	t_vector	pos;

	pos.y = on_screen_pos.y + on_map_pos.y * minimap->scale;
	pos.x = on_screen_pos.x + on_map_pos.x * minimap->scale;
	draw_square(image, pos, minimap->scale, minimap->floor_color);
}
