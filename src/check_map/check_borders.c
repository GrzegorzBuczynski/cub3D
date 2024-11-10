/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/10 19:17:08 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	**create_map_border(int width, int height)
{
	char	**map_border;
	int		i;

	map_border = malloc(sizeof(char *) * height);
	if (!map_border)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_border[i] = malloc(sizeof(char) * width);
		if (map_border[i] == NULL)
		{
			while (--i >= 0)
				free(map_border[i]);
			free(map_border);
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
	map_width = get_maps_max_row_width(map);
	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			if (map[y][x] != '\0' && ft_strchr("1NSEW", map[y][x]))
				map_border[y + 1][x + 1] = map[y][x];
			x++;
		}
		y++;
	}
}

static void	flood_fill(char **map, int height, int y, int x)
{
	int	width;

	width = get_maps_row_width(map[0]);
	if (y < 0 || y >= height || x < 0 || x >= width || map[y][x] == '1'
		|| map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, height, y - 1, x);
	flood_fill(map, height, y + 1, x);
	flood_fill(map, height, y, x - 1);
	flood_fill(map, height, y, x + 1);
	flood_fill(map, height, y - 1, x - 1);
	flood_fill(map, height, y - 1, x + 1);
	flood_fill(map, height, y + 1, x - 1);
	flood_fill(map, height, y + 1, x + 1);
}

int	check_borders(char **map)
{
	int			width;
	int			height;
	char		**map_border;
	int			status;
	t_vector	p_pos;

	width = get_maps_max_row_width(map) + 2;
	height = get_map_height(map) + 2;
	status = 1;
	map_border = create_map_border(width, height);
	if (!map_border)
		return (NULL);
	fill_map_border(map_border, width, height);
	copy_map_into_border(map_border, map);
	// print for testing
	print_map_nl(map_border);
	get_player_position(map, &p_pos);
	map_border[p_pos.y][p_pos.x] = '2';
	flood_fill(map_border, height, p_pos.y + 1, p_pos.x + 1);
	if (map_border[0][0] == '2')
		status = 0;
	// print for testing
	print_map_nl(map_border);
	free_map(map_border);
	return (status);
}
