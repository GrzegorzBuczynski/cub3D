/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/05 19:22:28 by gbuczyns         ###   ########.fr       */
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

void	draw_player(t_image *image, int y, int x)
{
	draw_square(image, y, x, PLAYER_COLOR);
}

void	draw_wall2(t_image *image, int y, int x)
{
	draw_square(image, y, x, WALL_COLOR);
}

void	draw_wall(t_image *image, t_vector on_screen_pos, t_vector on_map_pos)
{
	if (on_map_pos.x > 64)
	{
		printf("on_map_pos.y: %d\n", on_map_pos.y);
	}
	draw_square(image, on_screen_pos.y + on_map_pos.y * MINIMAP_SCALE,
		on_screen_pos.x + on_map_pos.x * MINIMAP_SCALE, WALL_COLOR);
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

void	draw_minimap_color(t_game *game, t_vector sm_pos, t_vector center)
{
	t_vector	mini_grid;

	mini_grid.x = center.x - PLAYER_RADIUS + sm_pos.x;
	mini_grid.y = center.y - PLAYER_RADIUS + sm_pos.y;
	if (mini_grid.y >= 0 && mini_grid.y < game->map.height && mini_grid.x >= 0
		&& mini_grid.x < ft_strlen(game->map.grid[mini_grid.y]))
	{
		if (game->map.grid[mini_grid.y][mini_grid.x] == '1')
			draw_wall2(&game->display.img, sm_pos.y * MINIMAP_SCALE
				+ MINIMAP_PADDING_Y, sm_pos.x * MINIMAP_SCALE
				+ MINIMAP_PADDING_X);
	}
	// else
	// 	draw_floor(&game->display.img, sm_pos.y * MINIMAP_SCALE
	// 		+ MINIMAP_PADDING_Y, sm_pos.x * MINIMAP_SCALE + MINIMAP_PADDING_X);
}

void	update_center(t_vector *center, t_game *game, int y)
{
	int	i;
	int	len;

	center->x = game->player.pos.x;
	center->y = game->player.pos.y;
	if (center->x < PLAYER_RADIUS)
		center->x = PLAYER_RADIUS;
	// if (y > game->map.height)
	// 	len = game->map.width;
	// else
	// 	len = game->map.height;
	// len = ft_strlen(game->map.grid[y]);
	if (center->x > game->map.width - PLAYER_RADIUS)
		center->x = game->map.width - PLAYER_RADIUS;
	if (center->y > game->map.height - PLAYER_RADIUS)
		center->y = game->map.height - PLAYER_RADIUS;
	if (center->y < PLAYER_RADIUS)
		center->y = PLAYER_RADIUS;
}

void	draw_minimap2(t_game *game)
{
	t_vector	sm_pos;
	t_vector	center;

	sm_pos.y = 0;
	while (sm_pos.y < 2 * PLAYER_RADIUS + 1)
	{
		sm_pos.x = 0;
		while (sm_pos.x < 2 * PLAYER_RADIUS + 1)
		{
			update_center(&center, game, sm_pos.y);
			draw_minimap_color(game, sm_pos, center);
			sm_pos.x++;
		}
		sm_pos.y++;
	}
}

void	draw_walls(t_game *game, t_vector m_pos_on_screen, t_vector size,
		t_vector center)
{
	int			y;
	int			x;
	t_vector	sm_pos;
	t_image		*image;
	t_vector	pos_on_grid;

	image = &game->display.img;
	pos_on_grid.y = center.y - PLAYER_RADIUS;
	sm_pos.y = 0;
	while (pos_on_grid.y < game->map.height && pos_on_grid.y < center.y
		+ PLAYER_RADIUS)
	{
		pos_on_grid.x = center.x - PLAYER_RADIUS;
		sm_pos.x = 0;
		while (pos_on_grid.x < ft_strlen(game->map.grid[pos_on_grid.y])
			&& pos_on_grid.x < center.x + PLAYER_RADIUS)
		{
			if (game->map.grid[pos_on_grid.y][pos_on_grid.x] == '1')
			{
				draw_wall(image, m_pos_on_screen, sm_pos);
			}
			pos_on_grid.x++;
			sm_pos.x++;
		}
		pos_on_grid.y++;
		sm_pos.y++;
	}
}

void	update_player_pos_on_screen(t_game *game, t_vector *p_pos_on_screen)
{
	p_pos_on_screen->y = PLAYER_RADIUS * MINIMAP_SCALE + MINIMAP_PADDING_Y;
	p_pos_on_screen->x = PLAYER_RADIUS * MINIMAP_SCALE + MINIMAP_PADDING_X;
}

void	draw_minimap(t_game *game)
{
	t_vector p_pos_on_screen; // player position
	draw_minimap_background(&game->display.img, MINIMAP_PADDING_Y,
		MINIMAP_PADDING_X, FLOOR_COLOR);
	draw_minimap2(game);
	update_player_pos_on_screen(game, &p_pos_on_screen);
	draw_player(&game->display.img, p_pos_on_screen.y, p_pos_on_screen.x);
}
