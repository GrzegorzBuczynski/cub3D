/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:39:33 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/13 17:54:43 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_player_on_map(char c, int *player)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*player)++;
	else if (c != '0' && c != '1' && c != ' ' && c != '\n' && c != 'B')
		return (0);
	return (1);
}

int	check_player(char **map)
{
	int	player;
	int	x;
	int	y;

	player = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (!is_player_on_map(map[y][x], &player))
				return (ft_error(1, "Error\nInvalid object on map.\n"));
			x++;
		}
		y++;
	}
	if (player == 0)
		return (ft_error(1, "Error\nMap doesn't have a player.\n"));
	if (player != 1)
		return (ft_error(1, "Error\nAdd only 1 player on the map.\n"));
	return (0);
}
