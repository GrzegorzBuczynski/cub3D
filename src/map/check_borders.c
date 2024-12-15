/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/15 16:09:30 by gbuczyns         ###   ########.fr       */
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

static void	flood_fill(char **map, t_vector pos, t_vector size)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= size.y || pos.x >= size.x)
		return ;
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == '3')
		return ;
	if (map[pos.y][pos.x] == '2' || map[pos.y][pos.x] == '0')
	{
		map[pos.y][pos.x] = '3';
		flood_fill(map, (t_vector){pos.y + 1, pos.x}, size);
		flood_fill(map, (t_vector){pos.y + 1, pos.x + 1}, size);
		flood_fill(map, (t_vector){pos.y + 1, pos.x - 1}, size);
		flood_fill(map, (t_vector){pos.y - 1, pos.x}, size);
		flood_fill(map, (t_vector){pos.y - 1, pos.x + 1}, size);
		flood_fill(map, (t_vector){pos.y - 1, pos.x - 1}, size);
		flood_fill(map, (t_vector){pos.y, pos.x + 1}, size);
		flood_fill(map, (t_vector){pos.y, pos.x + 1}, size);
	}
}

int	alloc_bigger_map(t_game *game, char ***map)
{
	int	i;
	int	j;
	char	**new_map;

	i = 0;
	new_map = gcalloc(sizeof(char *) * (game->map.height + 3), 1);
	if (!new_map)
		close_program(game);
	while (i < game->map.height + 2)
	{
		j = 0;
		new_map[i] = gmalloc(sizeof(char) * (game->map.width + 3));
		if (!new_map[i])
			close_program(game);
		while (j < game->map.width + 3)
		{
			new_map[i][j] = '2';
			j++;
		}
		i++;
		
	}
	*map = new_map;
}

void	rewrite_map(char **map, char **new_map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] && map[i][j] == '1')
				new_map[i + 1][j + 1] = '1';
			j++;
		}
		i++;
	}
}

print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	check_borders(t_game *game)
{
	char	**map;
	t_vector size;
	t_vector pos;

	game->map.width = get_maps_max_row_width(game->map.grid);
	game->map.height = get_map_height(game->map.grid);
	size = (t_vector){game->map.height, game->map.width};
	pos = (t_vector){game->player.pos.y + 1, game->player.pos.x + 1};
	alloc_bigger_map(game, &map);
	rewrite_map(game->map.grid, map);
	print_map(map);
	flood_fill(map, pos, size);
	if (map[0][0] == '3')
	{
		printf("Error\nMap is not closed.\n");
		close_program(&game->display);
	}
	return (0);
}
