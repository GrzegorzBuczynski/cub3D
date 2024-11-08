/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/08 16:32:56 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

bool	find_start_position(char **map, int *start_y, int *start_x)
{
	bool	player_found;
	int		y;
	int		x;

	y = 0;
	player_found = false;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == 'W'
				|| map[y][x] == 'E')
			{
				if (player_found)
					return (false);
				player_found = true;
				*start_y = y;
				*start_x = x;
			}
			x++;
		}
		y++;
	}
	return (player_found);
}

bool	check_boundary(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = -1;
		while (x++, map[y][x] != '\0')
			if ((y == 0 || x == 0 || map[y][x + 1] == '\0') && map[y][x] == 'V')
				return (false);
		y++;
	}
	return (true);
}

void	restore_visited_to_walls(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = -1;
		while (x++, map[y][x] != '\0')
			if (map[y][x] == 'V')
				map[y][x] = '0';
		y++;
	}
}

void	restore_player_position(char **map, int start_y, int start_x,
		char player_symbol)
{
	if (map[start_y] != NULL && map[start_y][start_x] != '\0')
		map[start_y][start_x] = player_symbol;
}

void	flood_fill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || map[y][x] == '\0')
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
	flood_fill(map, y + 1, x + 1);
	flood_fill(map, y - 1, x - 1);
	flood_fill(map, y + 1, x - 1);
	flood_fill(map, y - 1, x + 1);
}

bool	check_borders(char **map)
{
	int		start_y;
	int		start_x;
	char	original_char;

	start_y = -1;
	start_x = -1;
	if (!find_start_position(map, &start_y, &start_x))
		return (false);
	original_char = map[start_y][start_x];
	map[start_y][start_x] = 'V';
	flood_fill(map, start_y, start_x);
	if (!check_boundary(map))
	{
		restore_visited_to_walls(map);
		restore_player_position(map, start_y, start_x, original_char);
		return (false);
	}
	restore_visited_to_walls(map);
	restore_player_position(map, start_y, start_x, original_char);
	return (true);
}
