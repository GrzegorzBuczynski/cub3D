/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/09 18:35:09 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	get_player_position(char **map, t_vector *p_pos)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				p_pos->x = x;
				p_pos->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	printf("Error\nNo player starting position found in map\n");
}

int	get_maps_row_width(const char *row)
{
	int	length;

	length = strlen(row);
	if (length > 0 && row[length - 1] == '\n')
		return (length - 1);
	return (length);
}

int	get_maps_max_row_width(char **map)
{
	int	max_width;
	int	row_length;
	int	y;

	max_width = 0;
	y = 0;
	while (map[y])
	{
		row_length = get_maps_row_width(map[y]);
		if (row_length > max_width)
		{
			max_width = row_length;
		}
		y++;
	}
	return (max_width);
}

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i > height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
