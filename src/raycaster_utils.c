/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:26:39 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/03 17:01:49 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void	add_character_plane(t_game *game)
{
	char	plane;

	plane = game->player.direction;
	if (plane == 'S')
	{
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
	}
	else if (plane == 'N')
	{
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
	}
	else if (plane == 'E')
	{
		game->player.dir.x = 1;
		game->player.plane.y = 0.66;
	}
	else if (plane == 'W')
	{
		game->player.dir.x = -1;
		game->player.plane.y = -0.66;
	}
}

void	ray_direction_calculate(t_game *game, int x)
{
	game->rc.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->rc.raydir.y = game->player.dir.y + game->player.plane.y
		* game->rc.camera_x;
	game->rc.raydir.x = game->player.dir.x + game->player.plane.x
		* game->rc.camera_x;
	game->rc.map.x = (int)game->player.pos.y;
	game->rc.map.y = (int)game->player.pos.x;
	game->rc.delta_dist.y = fabs(1 / game->rc.raydir.y);
	game->rc.delta_dist.x = fabs(1 / game->rc.raydir.x);
}

void	calculate_step_and_dist(t_game *game)
{
	if (game->rc.raydir.y < 0)
	{
		game->rc.step.y = -1;
		game->rc.lenght_to.y = (game->player.pos.y - game->rc.map.x)
			* game->rc.delta_dist.y;
	}
	else
	{
		game->rc.step.y = 1;
		game->rc.lenght_to.y = (game->rc.map.x + 1.0 - game->player.pos.y)
			* game->rc.delta_dist.y;
	}
	if (game->rc.raydir.x < 0)
	{
		game->rc.step.x = -1;
		game->rc.lenght_to.x = (game->player.pos.x - game->rc.map.y)
			* game->rc.delta_dist.x;
	}
	else
	{
		game->rc.step.x = 1;
		game->rc.lenght_to.x = (game->rc.map.y + 1.0 - game->player.pos.x)
			* game->rc.delta_dist.x;
	}
}


