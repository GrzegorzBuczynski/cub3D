/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/04 18:57:53 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_pixel2(t_image *img, int y, int x, int color)
{
	int	i;
	int	*image;

	image = (int *)(img->pixel_data);
	image[y * SCREEN_WIDTH + x] = color;
}

void	draw_square(t_image *image, int y, int x, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			put_pixel2(image, y + i, x + j, color);
			j++;
		}
		i++;
	}
}

// void	draw_player(t_image *image, int y, int x)
// {
// 	draw_square(image, y, x, PLAYER_COLOR);
// }

void	draw_wall(t_image *image, int y, int x)
{
	draw_square(image, y, x, WALL_COLOR);
}

void	draw_floor(t_image *image, int y, int x)
{
	draw_square(image, y, x, FLOOR_COLOR);
}

t_vector	update_p_pos_on_minimap(t_vector *p_pos, int height, int width)
{
	t_vector	p_pos_mm;

	if (p_pos->y > PLAYER_RADIUS && p_pos->y < height - PLAYER_RADIUS)
		p_pos_mm.y = p_pos->y;
	if (p_pos->x > PLAYER_RADIUS && p_pos->x < width - PLAYER_RADIUS)
		p_pos_mm.x = p_pos->x;
	return (p_pos_mm);
}

void	draw_minimap(t_game *game)
{
	t_vector	p_pos;
	t_vector	p_pos_mm;
	t_vector	map_pos;
	t_vector	rend_pos;

	p_pos.x = (int)game->player.pos.x;
	p_pos.y = (int)game->player.pos.y;
	p_pos_mm = update_p_pos_on_minimap(&p_pos, game->map.height,
			game->map.width);
	map_pos.y = 0;
	if (p_pos.y <= PLAYER_RADIUS)
		rend_pos.y = 0;
	else
		rend_pos.y = p_pos.y - PLAYER_RADIUS;
	rend_pos.x = p_pos.x - PLAYER_RADIUS;
	while (rend_pos.y < (2 * PLAYER_RADIUS) + 1)
	{
		map_pos.x = 0;
		if (p_pos.x <= PLAYER_RADIUS)
			rend_pos.x = 0;
		else
			rend_pos.x = p_pos.x - PLAYER_RADIUS;
		while (rend_pos.x < (2 * PLAYER_RADIUS) + 1)
		{
			if ((rend_pos.y >= 0 && rend_pos.y < game->map.height)
				&& (rend_pos.x >= 0 && rend_pos.x < game->map.width))
			{
				if (game->map.grid[rend_pos.y][rend_pos.x] == '1')
					draw_wall(&game->display.img, map_pos.y * MINIMAP_SCALE
						+ MINIMAP_PADDING_Y, map_pos.x * MINIMAP_SCALE
						+ MINIMAP_PADDING_X);
			}
			rend_pos.x++;
			map_pos.x++;
		}
		rend_pos.y++;
		map_pos.y++;
	}
	draw_player(&game->display.img, p_pos.y, p_pos.x);
}

draw_wall(image, m_pos.y *MINIMAP_SCALE + MINIMAP_PADDING_Y,
	m_pos.x *MINIMAP_SCALE + MINIMAP_PADDING_X);

draw_player(&game->display.img, 100, 100);
