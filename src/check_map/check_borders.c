/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/10 00:06:25 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	error(const char *message, int code)
{
	fprintf(stderr, "%s", message);
	exit(code);
}

// Function to get the width of a row
int	get_maps_row_width(const char *row)
{
	int	length;

	length = strlen(row);
	if (length > 0 && row[length - 1] == '\n')
	{
		return (length - 1); // Exclude newline character if present
	}
	return (length);
}

// Function to get the maximum row width in the map
int	get_maps_max_row_width(char **map)
{
	int	max_width;
	int	i;
	int	row_length;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		row_length = get_maps_row_width(map[i]);
		if (row_length > max_width)
		{
			max_width = row_length;
		}
		i++;
	}
	return (max_width);
}

// Function to get the height of the map
int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
	{
		height++;
	}
	return (height);
}

// Helper function to fill the map border with '2'
void	fill_map_border(char **map_border, int width, int height)
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			map_border[i][j] = '2'; // Fill border with '2'
		}
	}
}

void	copy_map_into_border(char **map_border, char **map)
{
	int i, j;
	int map_height = get_map_height(map);
	int map_width = get_maps_max_row_width(map);

	for (i = 0; i < map_height; i++)
	{
		for (j = 0; j < map_width; j++)
		{
			// Copy '1' from map to map_border starting from position (1,1)
			if (map[i][j] == '1')
			{
				map_border[i + 1][j + 1] = '1';
			}
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (map[i][j] == 'N')
					map_border[i + 1][j + 1] = 'N';
				if (map[i][j] == 'S')
					map_border[i + 1][j + 1] = 'S';
				if (map[i][j] == 'W')
					map_border[i + 1][j + 1] = 'W';
				if (map[i][j] == 'E')
					map_border[i + 1][j + 1] = 'E';
			}
		}
	}
}

void	get_player_position(char **map, t_vector *p_pos)
{	
	for (int y = 0; map[y] != NULL; y++)
	{
		for (int x = 0; map[y][x] != '\0'; x++)
		{
			if (map[y][x] == 'S' || map[y][x] == 'N'
				|| map[y][x] == 'W' || map[y][x] == 'E')
			{
				// Save player coordinates
				p_pos->x = x;
				p_pos->y = y;
				return ; // Exit function once player position is found
			}
		}
	}
	// If we reach here, no player position was found
	printf("Error: No player starting position found in map\n");
}

static void	flood_fill(char **map, int height, int y, int x)
{
	int	width;

	width = get_maps_max_row_width(map);
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

// Main function to check borders
int	check_borders(char **map)
{
	int width = get_maps_max_row_width(map) + 2;
	int height = get_map_height(map) + 2;
	char **map_border;
	int i;
	t_vector p_pos;

	// Allocate memory for map_border
	map_border = malloc(sizeof(char *) * height);
	if (map_border == NULL)
		return (-1);

	for (i = 0; i < height; i++)
	{
		map_border[i] = malloc(sizeof(char) * width);
		if (map_border[i] == NULL)
		{
			while (i-- > 0)
				free(map_border[i]);
			free(map_border);
			return (-1);
		}
	}
	fill_map_border(map_border, width, height);
	copy_map_into_border(map_border, map);
	print_map_nl(map_border);
	for (i = 0; i < height; i++)
		free(map_border[i]);
	free(map_border);
	get_player_position(map, &p_pos);
	flood_fill(map_border, height, p_pos.y, p_pos.x);
	print_map_nl(map_border);
	return (0);
}
