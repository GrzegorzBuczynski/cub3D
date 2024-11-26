/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/26 18:39:52 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_minimap(t_minimap *m_map, t_display *display)
{
	m_map->display = display;
	m_map->start_x = MINIMAP_PADDING;
	m_map->start_y = MINIMAP_PADDING;
	m_map->cell_size = MINIMAP_SCALE;
	m_map->map_y = 0;
}

int	get_tile_color(char tile)
{
	if (tile == '1')
		return (WALL_COLOR);
	else
		return (FLOOR_COLOR);
}

void	draw_square(t_display *display, t_square_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (i < params->size)
	{
		j = 0;
		while (j < params->size)
		{
			((int *)(&display->img.pixel_data))[(params->y + i) * SCREEN_WIDTH
				+ (params->x + j)] = params->color;
			j++;
		}
		i++;
	}
}

// void	draw_minimap_item(t_minimap *m_map, t_game *game, int is_player)
// {
// 	t_square_params	params;

// 	if (!is_player)
// 	{
// 		params.color = get_tile_color(game->map2.grid[m_map->map_y][m_map->map_x]);
// 		params.x = m_map->start_x + (m_map->map_x * m_map->cell_size);
// 		params.y = m_map->start_y + (m_map->map_y * m_map->cell_size);
// 		params.size = m_map->cell_size;
// 		draw_square(m_map->display, &params);
// 	}
// 	else
// 	{
// 		params.x = m_map->start_x + (game->player.tile.x * m_map->cell_size);
// 		params.y = m_map->start_y + (game->player.tile.y * m_map->cell_size);
// 		params.size = m_map->cell_size / 2;
// 		params.color = PLAYER_COLOR;
// 		draw_square(m_map->display, &params);
// 	}
// }

// void	draw_minimap(t_game *game)
// {
// 	t_minimap	m_map;

// 	init_minimap(&m_map, &game->display);
// 	m_map.map_y = 0;
// 	while (m_map.map_y < game->map2.height)
// 	{
// 		m_map.map_x = 0;
// 		while (m_map.map_x < game->map2.width)
// 		{
// 			draw_minimap_item(&m_map, game, 0);
// 			m_map.map_x++;
// 		}
// 		m_map.map_y++;
// 	}
// 	draw_minimap_item(&m_map, game, 1);
// }
