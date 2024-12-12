/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/12 18:59:42 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	set_wall_x(t_game *game, t_wall *wall)
{
	if (game->rc.side == 0)
		wall->factor.x = game->player.pos.x + wall->perp_wall_dist
			* game->rc.raydir.x;
	else
		wall->factor.x = game->player.pos.y + wall->perp_wall_dist
			* game->rc.raydir.y;
	wall->factor.x -= floor(wall->factor.x);
	if (game->rc.side == 0 && game->rc.raydir.y > 0)
		wall->factor.x = 1 - wall->factor.x;
	if (game->rc.side == 1 && game->rc.raydir.x < 0)
		wall->factor.x = 1 - wall->factor.x;
}

void	set_distance(t_game *game, t_wall *wall)
{
	if (game->rc.side == 0)
		wall->perp_wall_dist = (game->rc.map.x - game->player.pos.y + (1
					- game->rc.step.y) / 2) / game->rc.raydir.y + 0.0001;
	else
		wall->perp_wall_dist = (game->rc.map.y - game->player.pos.x + (1
					- game->rc.step.x) / 2) / game->rc.raydir.x + 0.0001;
}

void	set_wall_height(t_wall *wall)
{
	wall->height = (int)(SCREEN_HEIGHT / wall->perp_wall_dist);
	wall->y_start = (SCREEN_HEIGHT - wall->height) / 2;
	wall->y_end = SCREEN_HEIGHT / 2 + wall->height / 2;
}

void	set_draw_limits(t_game *game, t_wall *wall)
{
	game->rc.draw_start = wall->y_start;
	if (game->rc.draw_start < 0)
		game->rc.draw_start = 0;
	game->rc.draw_end = wall->y_end;
	if (game->rc.draw_end > SCREEN_HEIGHT)
		game->rc.draw_end = SCREEN_HEIGHT - 1;
}
