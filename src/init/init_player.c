/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:28:56 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/02 16:13:29 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void find_player_on_map(t_game *game)
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

void init_player_n_plane_direction(t_game *game)
{
	game->player.ini_plane = 0.66;
	game->player.ini_dir = -1;
	if (game->player.direction == 'N')
	{
		game->rc.angle = M_PI/2;
		update_dir_n_plane(game);
	}
	else if (game->player.direction == 'S')
	{
		game->rc.angle = M_PI*3/2;
		update_dir_n_plane(game);
	}
	else if (game->player.direction == 'W')
	{
		game->rc.angle = 0;
		update_dir_n_plane(game);
	}
	else if (game->player.direction == 'E')
	{
		game->rc.angle = M_PI;
		update_dir_n_plane(game);
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