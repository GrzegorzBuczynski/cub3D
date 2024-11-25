/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/25 20:35:26 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define TEXWIDTH 64
#define TEXHEIGHT 64
#define HORIZONTAL 0
#define VERTICAL 1
#define PITCH 0

void	ray_direction_calculate(t_game *game, int x)
{
	game->rc.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->rc.raydir.x = game->player.dir.x + game->player.plane.x
		* game->rc.camera_x;
	game->rc.raydir.y = game->player.dir.y + game->player.plane.y
		* game->rc.camera_x;
	game->rc.map.x = (int)game->player.pos.x;
	game->rc.map.y = (int)game->player.pos.y;
	game->rc.delta_dist.x = fabs(1 / game->rc.raydir.x);
	game->rc.delta_dist.y = fabs(1 / game->rc.raydir.y);
}

void	calculate_step_and_dist(t_game *game)
{
	if (game->rc.raydir.x < 0)
	{
		game->rc.step.x = -1;
		game->rc.lenght_to.x = (game->player.pos.x - game->rc.map.x)
			* game->rc.delta_dist.x;
	}
	else
	{
		game->rc.step.x = 1;
		game->rc.lenght_to.x = (game->rc.map.x + 1.0 - game->player.pos.x)
			* game->rc.delta_dist.x;
	}
	if (game->rc.raydir.y < 0)
	{
		game->rc.step.y = -1;
		game->rc.lenght_to.y = (game->player.pos.y - game->rc.map.y)
			* game->rc.delta_dist.y;
	}
	else
	{
		game->rc.step.y = 1;
		game->rc.lenght_to.y = (game->rc.map.y + 1.0 - game->player.pos.y)
			* game->rc.delta_dist.y;
	}
}

void	set_ray_steps(t_game *game)
{
	game->rc.hit = 0;
	while (game->rc.hit == 0)
	{
		if (game->rc.lenght_to.x < game->rc.lenght_to.y)
		{
			game->rc.lenght_to.x += game->rc.delta_dist.x;
			game->rc.map.x += game->rc.step.x;
			game->rc.side = 0;
		}
		else
		{
			game->rc.lenght_to.y += game->rc.delta_dist.y;
			game->rc.map.y += game->rc.step.y;
			game->rc.side = 1;
		}
		if (game->map.map[game->rc.map.x][game->rc.map.y] > '0')
			game->rc.hit = 1;
	}
}

void	calculate_wall_parameters(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.perp_wall_dist = (game->rc.map.x - game->player.pos.x + (1
					- game->rc.step.x) / 2) / game->rc.raydir.x + 0.0001;
	else
		game->rc.perp_wall_dist = (game->rc.map.y - game->player.pos.y + (1
					- game->rc.step.y) / 2) / game->rc.raydir.y + 0.0001;
	game->rc.line_height = (int)(SCREEN_HEIGHT / game->rc.perp_wall_dist);
	game->rc.draw_start = -game->rc.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->rc.draw_start < 0)
		game->rc.draw_start = 0;
	game->rc.draw_end = game->rc.line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->rc.draw_end >= SCREEN_HEIGHT)
		game->rc.draw_end = SCREEN_HEIGHT - 1;
}

void	calculate_texture_coordinates(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.wall_x = game->player.pos.y + game->rc.perp_wall_dist
			* game->rc.raydir.y;
	else
		game->rc.wall_x = game->player.pos.x + game->rc.perp_wall_dist
			* game->rc.raydir.x;
	game->rc.wall_x -= floor(game->rc.wall_x);
	game->rc.tex_x = (int)(game->rc.wall_x * (double)TEXWIDTH);
	if (game->rc.side == 0 && game->rc.raydir.x > 0)
		game->rc.tex_x = TEXWIDTH - game->rc.tex_x - 1;
	if (game->rc.side == 1 && game->rc.raydir.y < 0)
		game->rc.tex_x = TEXWIDTH - game->rc.tex_x - 1;
	game->rc.step_size = 1.0 * TEXHEIGHT / game->rc.line_height;
	game->rc.tex_pos = (game->rc.draw_start - SCREEN_HEIGHT / 2
			+ game->rc.line_height / 2) * game->rc.step_size;
}
