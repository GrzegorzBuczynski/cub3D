/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/02 20:25:55 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define MINIMAP_SCALE 5
#define MINIMAP_PADDING_X 20
#define MINIMAP_PADDING_Y 20
#define PLAYER_RADIUS 7
#define WALL 1
#define FLOOR 2
#define PLAYER 3

#define FLOOR_COLOR COLOR_DISCO
#define WALL_COLOR COLOR_GRAY
#define PLAYER_COLOR COLOR_RED

typedef struct s_square
{
	int size;
	int color;
} t_square;

void put_pixel2(t_image *img, int y, int x, int color)
{
	int i;
	int *image;

	image = (int *)(img->pixel_data);
	image[y * SCREEN_WIDTH + x] = color;
}

void draw_square(t_image *image, int y, int x, unsigned int color)
{
	int i;
	int j;

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

void draw_player(t_image *image, int y, int x)
{
	draw_square(image, y, x, PLAYER_COLOR);
}

void draw_wall(t_image *image, int y, int x)
{
	draw_square(image, y, x, WALL_COLOR);
}

void draw_floor(t_image *image, int y, int x)
{
	draw_square(image, y, x, FLOOR_COLOR);
}

void draw_minimap(t_game *game)
{
	int y;
	int x;
	t_vector p_pos;

	p_pos.x = (int)game->player.pos.x;
	p_pos.y = (int)game->player.pos.y;

	y = p_pos.y - PLAYER_RADIUS;
	while (y < p_pos.y + PLAYER_RADIUS)
	{
		x = x - PLAYER_RADIUS;
		while ()
		{
			x++;
		}
		y++;
	}
	draw_player(&game->display.img, 100, 100);
}

void temp(t_game *game)
{
	y = pos->y;
	while (y < (2 * PLAYER_RADIUS) + 1)
	{
		x = pos->x;
		while (x < (2 * PLAYER_RADIUS) + 1)
		{
			if (map.grid[y - PLAYER_RADIUS][x - PLAYER_RADIUS] == '1')
				draw_wall(image, y, x);
			else if (map.grid[y - PLAYER_RADIUS][x - PLAYER_RADIUS] == '0')
				draw_floor(image, y, x);
			else
				draw_player(image, y, x);
		}
	}
}

https://prod.liveshare.vsengsaas.visualstudio.com/join?92382A78A91E7ED2D41FC91B0424F106AD21