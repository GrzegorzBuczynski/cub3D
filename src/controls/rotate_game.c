/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:08:29 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/06 16:43:07 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_dir_n_plane(t_game *game)
{
	game->player.dir.x = -1 * cos(game->rc.angle + game->rc.mouse_angle);
	game->player.dir.y = -1 * sin(game->rc.angle + game->rc.mouse_angle);
	game->player.plane.y = game->player.dir.x * game->player.init_plane;
	game->player.plane.x = -game->player.dir.y * game->player.init_plane;
}

void	rotate_right(t_game *game, double speed)
{
	game->rc.angle += ROTATION_SPEED * game->rc.time_ratio * speed;
	if (game->rc.angle >= 2 * M_PI)
		game->rc.angle = game->rc.angle - 2 * M_PI;
	update_dir_n_plane(game);
}

void	rotate_left(t_game *game, double speed)
{
	game->rc.angle -= ROTATION_SPEED * game->rc.time_ratio * speed;
	if (game->rc.angle < 0)
		game->rc.angle = game->rc.angle + 2 * M_PI;
	update_dir_n_plane(game);
}
