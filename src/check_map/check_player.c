/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:39:33 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/09 00:17:14 by ssuchane         ###   ########.fr       */
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
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			if (!is_player_on_map(map[y][x], &player))
				return (ft_error(1, "Invalid object on map.\n"));
			x++;
		}
		y++;
	}
	if (player == 0)
		ft_panic("Map doesn't have a player.\n", 1);
	if (player != 1)
		ft_panic("There must be exactly 1 player on the map.\n", 1);
	// for testing
	printf("Player is on the map\n");
	return (0);
}
