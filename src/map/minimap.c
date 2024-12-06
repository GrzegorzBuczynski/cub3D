/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/06 16:03:58 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	draw_player(t_game *game, t_vector pos, int size, unsigned int color)
{
	t_image *image;
	t_line	direction;
	t_dvector	p_dir;

	p_dir = game->player.dir;
	image = &game->display.img;
	direction.color = color;
	direction.thickness = 5;
	direction.s = (t_vector){pos.y + size / 2, pos.x + size / 2};
	direction.f = (t_vector){direction.s.y + p_dir.y * size * 2, direction.s.x + p_dir.x * size * 2};
	draw_square(image, pos, size, color);
	draw_line(&direction, image);
}

void	draw_wall(t_image *image, t_vector on_screen_pos, t_vector on_map_pos, t_minimap *minimap)
{
	t_vector	pos;

	pos.y = on_screen_pos.y + on_map_pos.y * minimap->scale;
	pos.x = on_screen_pos.x + on_map_pos.x * minimap->scale;
	draw_square(image, pos, minimap->scale, minimap->wall_color);
}

void	draw_floor(t_image *image, t_vector on_screen_pos, t_vector on_map_pos, t_minimap *minimap)
{
	t_vector	pos;

	pos.y = on_screen_pos.y + on_map_pos.y * minimap->scale;
	pos.x = on_screen_pos.x + on_map_pos.x * minimap->scale;
	draw_square(image, pos, minimap->scale, minimap->floor_color);
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
	if (center->y > game->map.height - minimap->player_vision_range)
		center->y = game->map.height - minimap->player_vision_range;
	if (center->y < minimap->player_vision_range)
		center->y = minimap->player_vision_range;
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
	t_minimap	*minimap;

	minimap = &game->params.minimap;
	mini_grid.x = center.x - minimap->player_vision_range + mini_screen_grid_nbr.x;
	mini_grid.y = center.y - minimap->player_vision_range + mini_screen_grid_nbr.y;
	if (mini_grid.y >= 0 && mini_grid.y < game->map.height && mini_grid.x >= 0
		&& mini_grid.x < ft_strlen(game->map.grid[mini_grid.y]))
	{
		if (game->map.grid[mini_grid.y][mini_grid.x] == '1')
			draw_wall(&game->display.img, mini_padding, mini_screen_grid_nbr, minimap);
		else
			draw_floor(&game->display.img, mini_padding, mini_screen_grid_nbr, minimap);
	}
	else
		draw_floor(&game->display.img, mini_padding, mini_screen_grid_nbr, minimap);

}

void	draw_minimap(t_game *game, t_vector size, t_vector mini_padding, t_vector center)
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

void	add_minimap(t_game *game)
{
	t_vector	p_pos_on_screen; // player position
	t_vector	center;

	update_center(&center, game);
	draw_minimap(game, game->params.minimap.size, game->params.minimap.padding, center);
	update_player_pos_on_screen(game, &p_pos_on_screen, center);
	draw_player(game, p_pos_on_screen, game->params.minimap.scale, game->params.minimap.player_color);
}

/* 

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

void	set_player_position(t_game *game, t_vector *p_pos)
{
	p_pos->x = (int)game->player.pos.x;
	p_pos->y = (int)game->player.pos.y;
}

void	adjust_map_position(t_game *game, t_vector *map_pos, t_vector *off)
{
	if (map_pos->y <= PLAYER_RADIUS)
		map_pos->y = 0;
	else
		map_pos->y = map_pos->y - PLAYER_RADIUS;
	off->y = map_pos->y + (2 * PLAYER_RADIUS);
	if (map_pos->y + ((2 * PLAYER_RADIUS) + 1) >= game->map.height)
		map_pos->y = game->map.height - ((2 * PLAYER_RADIUS) + 1);
}

void	adjust_horizontal_map_position(t_game *game, t_vector *p_pos,
		t_vector *map_pos, t_vector *off)
{
	if (p_pos->x <= PLAYER_RADIUS)
		map_pos->x = 0;
	else
		map_pos->x = p_pos->x - PLAYER_RADIUS;
	off->x = map_pos->x + (2 * PLAYER_RADIUS) + 1;
	if (map_pos->x + ((2 * PLAYER_RADIUS) + 1) >= game->map.width)
		map_pos->x = game->map.width - ((2 * PLAYER_RADIUS) + 1);
}

void	draw_map_tile(t_game *game, t_vector map_pos, t_vector render_pos)
{
	if ((map_pos.y >= 0 && map_pos.y < game->map.height) && (map_pos.x >= 0
			&& map_pos.x < ft_strlen(game->map.grid[map_pos.y])))
	{
		if (game->map.grid[map_pos.y][map_pos.x] == '1')
			draw_wall(&game->display.img, render_pos.y * MINIMAP_SCALE
				+ MINIMAP_PADDING_Y, render_pos.x * MINIMAP_SCALE
				+ MINIMAP_PADDING_X);
	}
}

int	get_map_center_axis(int axis)
{
	int	screen_width;
	int	screen_height;

	screen_width = SCREEN_WIDTH;
	screen_height = SCREEN_HEIGHT;
	if (axis == 0)
	{
		return ((screen_width / 2) - (MINIMAP_SCALE / 2) - MINIMAP_PADDING_X);
	}
	else if (axis == 1)
	{
		return ((screen_height / 2) - (MINIMAP_SCALE / 2) - MINIMAP_PADDING_Y);
	}
	return (-1);
}

void	draw_minimap(t_game *game)
{
	t_vector	p_pos;
	t_vector	render_pos;
	t_vector	map_pos;
	t_vector	p_pos_mm;
	t_vector	off;

	set_player_position(game, &p_pos);
	render_pos.y = 0;
	map_pos.y = p_pos.y;
	adjust_map_position(game, &map_pos, &off);
	while (map_pos.y < off.y)
	{
		render_pos.x = 0;
		adjust_horizontal_map_position(game, &p_pos, &map_pos, &off);
		while (map_pos.x < off.x)
		{
			draw_map_tile(game, map_pos, render_pos);
			map_pos.x++;
			render_pos.x++;
		}
		map_pos.y++;
		render_pos.y++;
	}
	if (p_pos.x <= PLAYER_RADIUS || p_pos.x + PLAYER_RADIUS >= game->map.width)
		p_pos_mm.x = get_map_center_axis(0);
	else
		p_pos_mm.x = p_pos.x;
	if (p_pos.y <= PLAYER_RADIUS || p_pos.y + PLAYER_RADIUS >= game->map.height)
		p_pos_mm.y = get_map_center_axis(1);
	else
		p_pos_mm.y = p_pos.y;
	draw_player(&game->display.img, p_pos_mm.y, p_pos_mm.x);
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
} */
