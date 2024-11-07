/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:39:33 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/07 20:19:13 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	check_player(char c, int *player)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*player)++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

void	is_player_on_map(char **map)
{
	int	player;
	int	i;
	int	j;

	player = 0;
	i = -1;
	while (++i, map[i])
	{
		j = -1;
		while (++j, map[i][j])
			if (!check_player(map[i][j], &player))
				error(map, "Map doesn't have a player.");
	}
	if (player != 1)
		error(map, "There must be exactly 1 player on the map.");
}
