/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/05 19:39:54 by gbuczyns         ###   ########.fr       */
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
	draw_square(image, on_screen_pos.y + on_map_pos.y * MINIMAP_SCALE,
		on_screen_pos.x + on_map_pos.x * MINIMAP_SCALE, WALL_COLOR);
}

void	draw_floor(t_image *image, t_vector on_screen_pos, t_vector on_map_pos)
{
	draw_square(image, on_screen_pos.y + on_map_pos.y * MINIMAP_SCALE,
	on_screen_pos.x + on_map_pos.x * MINIMAP_SCALE, FLOOR_COLOR);
}

void	draw_minimap_background(t_image *image, int y, int x,
		unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (2 * PLAYER_MINIMAP_VISION_RANGE) + 1)
	{
		j = 0;
		while (j < (2 * PLAYER_MINIMAP_VISION_RANGE) + 1)
		{
			draw_square(image, i * MINIMAP_SCALE + y, j * MINIMAP_SCALE + x,
				color);
			j++;
		}
		i++;
	}
}


void	update_center(t_vector *center, t_game *game)
{
	int	i;
	int	len;
	t_minimap	*minimap;

	minimap = &game->params.minimap;
	center->x = game->player.pos.x;
	center->y = game->player.pos.y;
	if (center->x < minimap->size.x / 2)
		center->x = minimap->size.x / 2;
	if (center->x > game->map.width - minimap->size.x / 2)
		center->x = game->map.width - minimap->size.x / 2;
	if (center->y > game->map.height - minimap->size.y / 2)
		center->y = game->map.height - minimap->size.y / 2;
	if (center->y < minimap->size.y / 2)
		center->y = minimap->size.y / 2;
}

void	update_player_pos_on_screen(t_game *game, t_vector *p_pos_on_screen,
		t_vector center)
{
	t_minimap	*minimap;

	minimap = &game->params.minimap;
	p_pos_on_screen->y = minimap->size.y / 2 * minimap->scale + minimap->padding.y;
	p_pos_on_screen->x = minimap->size.x / 2 * minimap->scale + minimap->padding.y;
	if (game->player.pos.y < minimap->player_vision_range)
		p_pos_on_screen->y = ((int)game->player.pos.y) * minimap->scale
			+ minimap->padding.y;
	if (game->player.pos.y > game->map.height - minimap->player_vision_range)
		p_pos_on_screen->y = (((int)game->player.pos.y) - center.y + minimap->player_vision_range)
			* minimap->scale + minimap->padding.y;
	if (game->player.pos.x < minimap->player_vision_range)
		p_pos_on_screen->x = (int)game->player.pos.x * minimap->scale
			+ minimap->padding.x;
	if (game->player.pos.x > game->map.width - minimap->player_vision_range)
		p_pos_on_screen->x = ((int)game->player.pos.x - center.x + minimap->player_vision_range)
			* minimap->scale + minimap->padding.x;
}

void	draw_minimap_color(t_game *game, t_vector mini_padding, t_vector mini_screen_grid_nbr, t_vector center)
{
	t_vector	mini_grid;

	mini_grid.x = center.x - PLAYER_MINIMAP_VISION_RANGE + mini_screen_grid_nbr.x;
	mini_grid.y = center.y - PLAYER_MINIMAP_VISION_RANGE + mini_screen_grid_nbr.y;
	if (mini_grid.y >= 0 && mini_grid.y < game->map.height && mini_grid.x >= 0
		&& mini_grid.x < ft_strlen(game->map.grid[mini_grid.y]))
	{
		if (game->map.grid[mini_grid.y][mini_grid.x] == '1')
			draw_wall(&game->display.img, mini_padding, mini_screen_grid_nbr);
		else
			draw_floor(&game->display.img, mini_padding, mini_screen_grid_nbr);
	}
	else
		draw_floor(&game->display.img, mini_padding, mini_screen_grid_nbr);

}

void	draw_minimap2(t_game *game, t_vector size, t_vector mini_padding, t_vector center)
{
	t_vector	mini_screen_grid_nbr;

	mini_screen_grid_nbr.y = 0;
	while (mini_screen_grid_nbr.y < size.y)
	{
		mini_screen_grid_nbr.x = 0;
		while (mini_screen_grid_nbr.x < size.x)
		{
			draw_minimap_color(game, mini_padding, mini_screen_grid_nbr, center);
			mini_screen_grid_nbr.x++;
		}
		mini_screen_grid_nbr.y++;
	}
}




void	draw_minimap(t_game *game)
{
	t_vector	p_pos_on_screen; // player position
	t_vector	mini_padding;
	t_vector	center;
	t_vector	size;

	update_center(&center, game);
	draw_minimap2(game, game->params.minimap.size, game->params.minimap.padding, center);
	update_player_pos_on_screen(game, &p_pos_on_screen, center);
	draw_player(&game->display.img, p_pos_on_screen.y, p_pos_on_screen.x);
}

/* 

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
} */