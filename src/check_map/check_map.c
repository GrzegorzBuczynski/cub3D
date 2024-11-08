/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:38:53 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/08 17:17:41 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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

static int	find_first_row_of_map(char **array)
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

static void	convert_space_to_wall(char **map)
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

void	check_map(char **map)
{
	int	y;

	y = find_first_row_of_map(map);
	convert_space_to_wall(&map[y]);
	check_borders(map);
	check_player(&map[y]);
}
