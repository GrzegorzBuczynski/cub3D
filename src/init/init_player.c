/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:28:56 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/26 20:13:35 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void find_player_on_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
				|| game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				game->player.direction = game->map.map[i][j];
				game->map.map[i][j] = '0';
				game->player.pos.x = i + 0.5;
				game->player.pos.y = j + 0.5;
			}
			j++;
		}
		i++;
	}
	
}

void init_player_n_plane_direction(t_game *game)
{
	if (game->player.direction == 'N')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
	else if (game->player.direction == 'S')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
	else if (game->player.direction == 'E')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	else if (game->player.direction == 'W')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
}

void	init_player(t_game *game)
{
	find_player_on_map(game);
	init_player_n_plane_direction(game);
}


// void	init_player2(t_data *data)
// {
// 	data->angle = 0;
// 	data->initial_plane = INITIAL_PLANE__SIZE;
// 	data->initial_playerdir = INITIAL_PLAYERDIR;
// 	data->playerdir.x = data->initial_playerdir * sin(data->angle * M_PI / 180);
// 	data->playerdir.y = data->initial_playerdir * cos(data->angle * M_PI / 180);
// 	data->plane.x = data->initial_plane * cos(data->angle * M_PI / 180);
// 	data->plane.y = data->initial_plane * sin(data->angle * M_PI / 180);
// 	data->time = 0;
// 	data->oldTime = 0;
// 	data->game->player.pos.x = 10.0;
// 	data->game->player.pos.y = 11.5;
// 	data->game->player.step_size = STEP_SIZE;
// 	data->game->player.step_side_side.y = data->game->player.step_size
// 		* sin(data->angle * M_PI / 180);
// 	data->game->player.step_side_side.x = data->game->player.step_size
// 		* cos(data->angle * M_PI / 180);
// 	data->game->player.step_top_down.y = data->game->player.step_size
// 		* cos(data->angle * M_PI / 180);
// 	data->game->player.step_top_down.x = -data->game->player.step_size
// 		* sin(data->angle * M_PI / 180);
// }