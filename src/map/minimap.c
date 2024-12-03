/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/03 19:31:30 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define MINIMAP_SCALE 8
#define MINIMAP_PADDING_X 20
#define MINIMAP_PADDING_Y 20
#define PLAYER_RADIUS 10
#define FLOOR_COLOR COLOR_BROWN
#define WALL_COLOR COLOR_AQUA
#define PLAYER_COLOR COLOR_GOLD

typedef struct s_square
{
	int	size;
	int	color;
}		t_square;

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

void	draw_player(t_image *image, int y, int x)
{
	draw_square(image, y, x, PLAYER_COLOR);
}

void	draw_wall(t_image *image, int y, int x)
{
	draw_square(image, y, x, WALL_COLOR);
}

void	draw_floor(t_image *image, int y, int x)
{
	draw_square(image, y, x, FLOOR_COLOR);
}

void	draw_minimap_background(t_image *image, int y, int x,
		unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (2 * PLAYER_RADIUS) + 1)
	{
		j = 0;
		while (j < (2 * PLAYER_RADIUS) + 1)
		{
			draw_square(image, i * MINIMAP_SCALE + y, j * MINIMAP_SCALE + x,
				color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int			y;
	int			x;
	t_vector	p_pos;
	t_vector	m_pos;
	t_image		*image;

	p_pos.x = (int)game->player.pos.x;
	p_pos.y = (int)game->player.pos.y;
	image = &game->display.img;
	y = p_pos.y - PLAYER_RADIUS;
	// draw_minimap_background(image, MINIMAP_PADDING_Y, MINIMAP_PADDING_X,
		// FLOOR_COLOR);
	m_pos.y = 0;
	m_pos.x = 0;
	while (y < p_pos.y + PLAYER_RADIUS)
	{
		x = p_pos.x - PLAYER_RADIUS;
		m_pos.x = 0;
		while (x < p_pos.x + PLAYER_RADIUS)
		{
			if ((y >= 0 && y < game->map.height) && (x >= 0
					&& x < game->map.width))
			{
				if (game->map.grid[y][x] == '1')
					draw_wall(image, m_pos.y * MINIMAP_SCALE
						+ MINIMAP_PADDING_Y, m_pos.x * MINIMAP_SCALE
						+ MINIMAP_PADDING_X);
			}
			x++;
			m_pos.x++;
		}
		y++;
		m_pos.y++;
	}
	draw_player(&game->display.img, 100, 100);
}
