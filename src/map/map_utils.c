/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/13 19:09:28 by gbuczyns         ###   ########.fr       */
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
	gexit(1);
}

int	get_maps_row_width(char *row)
{
	int	length;

	length = 0;
	while (row[length] && row[length] != '\n')
		length++;
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
		gfree(map[i]);
		i++;
	}
	gfree(map);
}
