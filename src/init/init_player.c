/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:28:56 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/06 16:10:39 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	find_player_on_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				game->player.direction = game->map.grid[i][j];
				game->map.grid[i][j] = '0';
				game->player.pos.y = i + 0.5;
				game->player.pos.x = j + 0.5;
			}
			j++;
		}
		i++;
	}
	if (!game->player.direction)
		perror("Error!\nNo player on the map!\n.");
	// TO DO ---------
	// NIE DOPUSCIC DO STARTU PROGRAMU
}

void	init_player_n_plane_direction(t_game *game)
{
	if (game->player.direction == 'N')
	{
		game->rc.angle = M_PI / 2;
	}
	else if (game->player.direction == 'S')
	{
		game->rc.angle = M_PI * 3 / 2;
	}
	else if (game->player.direction == 'W')
	{
		game->rc.angle = 0;
	}
	else if (game->player.direction == 'E')
	{
		game->rc.angle = M_PI;
	}
	update_dir_n_plane(game);
}

void	init_player(t_game *game)
{
	game->player.init_plane = FOV / 100;
	find_player_on_map(game);
	init_player_n_plane_direction(game);
}
