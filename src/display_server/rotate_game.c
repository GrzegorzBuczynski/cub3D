/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:08:29 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/25 18:47:53 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(-ROTATION_SPEED)
		- game->player.dir.y * sin(-ROTATION_SPEED);
	game->player.dir.y = old_dir_x * sin(-ROTATION_SPEED) + game->player.dir.y
		* cos(-ROTATION_SPEED);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(-ROTATION_SPEED)
		- game->player.plane.y * sin(-ROTATION_SPEED);
	game->player.plane.y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->player.plane.y * cos(-ROTATION_SPEED);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(ROTATION_SPEED)
		- game->player.dir.y * sin(ROTATION_SPEED);
	game->player.dir.y = old_dir_x * sin(ROTATION_SPEED) + game->player.dir.y
		* cos(ROTATION_SPEED);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(ROTATION_SPEED)
		- game->player.plane.y * sin(ROTATION_SPEED);
	game->player.plane.y = old_plane_x * sin(ROTATION_SPEED)
		+ game->player.plane.y * cos(ROTATION_SPEED);
}

