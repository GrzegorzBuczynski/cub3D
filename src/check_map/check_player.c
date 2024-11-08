/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:39:33 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/08 17:18:39 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	is_player_on_map(char c, int *player)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*player)++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

int	check_player(char **map)
{
	int	player;
	int	x;
	int	y;

	player = 0;
	y = -1;
	while (++y, map[y])
	{
		x = -1;
		while (++x, map[y][x])
			if (!is_player_on_map(map[y][x], &player))
				return (ft_error(1, "Map doesn't have a player.\n"));
	}
	if (player != 1)
		return (ft_error(1, "There must be exactly 1 player on the map.\n"));
	return (0);
}
