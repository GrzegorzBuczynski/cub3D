/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:09:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/15 16:35:28 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	only_whitespace_before(char *array, int x)
{
	while (x >= 0)
	{
		if (x == 0)
			return (1);
		x--;
		if (array[x] != ' ')
			return (0);
		if (array[x] == ' ')
			continue ;
	}
	return (1);
}

void	convert_spaces_to_walls(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				map[y][x] = '1';
			x++;
		}
		y++;
	}
}

static int	find_first_map_row(char **array)
{
	int	x;
	int	y;

	y = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (array[y][x] == '1' && only_whitespace_before(array[y], x))
				return (y);
			x++;
		}
		y++;
	}
	return (y);
}

char	**create_map_copy(char **map)
{
	char	**map_cpy;
	int		height;
	int		y;
	int		x;

	y = 0;
	height = get_map_height(map);
	map_cpy = gcalloc(sizeof(char *) * height + 1, 1);
	while (map[y])
	{
		x = 0;
		map_cpy[y] = gcalloc(sizeof(char) * (ft_strlen(map[y]) + 1), 1);
		while (map[y][x])
		{
			map_cpy[y][x] = map[y][x];
			x++;
		}
		y++;
	}
	return (map_cpy);
}

void	select_map(t_game *data)
{
	int	y;

	y = find_first_map_row(data->array);
	data->map.grid = &data->array[y];
}
