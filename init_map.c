/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:09:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/08 20:11:02 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	convert_space_to_wall(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (i++, map[i])
	{
		j = -1;
		while (j++, map[i][j])
			if (map[i][j] == ' ')
				map[i][j] = '1';
	}
}

static int	find_first_map_row(char **array)
{
	int	x;
	int	y;

	y = 0;
	while (array[y])
	{
		x = -1;
		while (x++, array[y][x])
			if (array[y][x] == '1' && only_whitespace_before(array[y], x))
				return (y);
		y++;
	}
	return (y);
}

void	select_map(t_game *data)
{
	int	y;

	y = find_first_map_row(data->array);
	data->map = data->array + y;
	print_map(data->map);
	convert_space_to_wall(data->map);
	print_map(data->map);
}
