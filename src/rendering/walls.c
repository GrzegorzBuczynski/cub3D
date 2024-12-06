/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/04 19:43:54 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

typedef struct s_wall
{
	int			height;
	double		perp_wall_dist;
	int			y_start;
	int			y_end;
	t_dvector	factor;
}				t_wall;

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

void	set_wall_height(t_game *game, t_wall *wall)
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

int	scan_for_hit(t_game *game, char c)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->rc.lenght_to.y < game->rc.lenght_to.x)
		{
			game->rc.lenght_to.y += game->rc.delta_dist.y;
			game->rc.map.x += game->rc.step.y;
			game->rc.side = 0;
		}
		else
		{
			game->rc.lenght_to.x += game->rc.delta_dist.x;
			game->rc.map.y += game->rc.step.x;
			game->rc.side = 1;
		}
		if (game->map.grid[game->rc.map.x][game->rc.map.y] == c)
		{
			hit = 1;
			return (1);
		}
		else if (game->map.grid[game->rc.map.x][game->rc.map.y] == '1')
		{
			hit = 1;
			return (0);
		}
	}
}

void	draw_object(t_game *game, char c)
{
	int				x;
	int				y;
	unsigned int	color;
	t_wall			wall;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		set_ray_direction(game, x);
		set_step_and_dist(game);
		if (scan_for_hit(game, c) == 0)
			continue ;
		set_wall_x(game, &wall);
		set_distance(game, &wall);
		set_wall_height(game, &wall);
		set_draw_limits(game, &wall);
		game->rc.tex_img = get_texture(game, c, game->rc.sec_part);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
		{
			wall.factor.y = ((double)y - wall.y_start) / wall.height;
			color = get_texture_pixel(game->rc.tex_img, wall.factor.y,
					wall.factor.x);
			color = scale_color(color, wall.perp_wall_dist / 30);
			put_pixel(&game->display.img, x, y, color);
		}
	}
}
