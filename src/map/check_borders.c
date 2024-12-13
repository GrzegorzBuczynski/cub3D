/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/13 17:52:09 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	**create_map_border(int width, int height)
{
	char	**map_border;
	int		i;

	map_border = gmalloc(sizeof(char *) * height);
	if (!map_border)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_border[i] = gmalloc(sizeof(char) * width);
		if (map_border[i] == NULL)
		{
			while (--i >= 0)
				gfree(map_border[i]);
			gfree(map_border);
			return (NULL);
		}
		i++;
	}
	return (map_border);
}

void	fill_map_border(char **map_border, int width, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			map_border[y][x] = '2';
			x++;
		}
		y++;
	}
}

void	copy_map_into_border(char **map_border, char **map)
{
	int	map_height;
	int	map_width;
	int	y;
	int	x;

	map_height = get_map_height(map);
	y = 0;
	while (y < map_height)
	{
		x = 0;
		map_width = get_maps_row_width(map[y]);
		while (x < map_width)
		{
			if (map[y][x] && ft_strchr("1NSEW", map[y][x]))
				map_border[y + 1][x + 1] = map[y][x];
			x++;
		}
		y++;
	}
}

static void	flood_fill(t_map *map, int height, int y, int x)
{
	int	width;

	width = map->max_width;
	if (y < 0 || y >= height || x < 0 || x >= width || map->grid[y][x] == '1'
		|| map->grid[y][x] == 'V')
		return ;
	map->grid[y][x] = 'V';
	flood_fill(map, height, y - 1, x);
	flood_fill(map, height, y + 1, x);
	flood_fill(map, height, y, x - 1);
	flood_fill(map, height, y, x + 1);
	flood_fill(map, height, y - 1, x - 1);
	flood_fill(map, height, y - 1, x + 1);
	flood_fill(map, height, y + 1, x - 1);
	flood_fill(map, height, y + 1, x + 1);
}

int	check_borders(t_map *map)
{
	int			width;
	int			height;
	char		**map_border;
	int			status;
	t_vector	p_pos;

	width = get_maps_max_row_width(map->grid) + 2;
	height = get_map_height(map->grid) + 2;
	status = 1;
	map_border = create_map_border(width, height);
	if (!map_border)
		return (1);
	fill_map_border(map_border, width, height);
	convert_spaces_to_walls(map->grid);
	copy_map_into_border(map_border, map->grid);
	get_player_position(map->grid, &p_pos);
	map_border[p_pos.y][p_pos.x] = '2';
	flood_fill(map, height, p_pos.y + 1, p_pos.x + 1);
	if (map_border[0][0] == '2')
		status = 0;
	free_map(map_border, height);
	return (status);
}
