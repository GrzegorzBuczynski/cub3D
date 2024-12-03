/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/03 17:05:28 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define HORIZONTAL 0
#define VERTICAL 1



typedef struct s_wall
{
	int		wall_start;
	int		wall_end;
	int		wall_height;
	int		wall_y;
	// double	tex_y;
}			t_wall;

typedef struct t_texture
{	
	t_dvector	pos;
	t_image		*image;
	
}		t_texture;


void	calculate_wall_parameters(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.perp_wall_dist = (game->rc.map.x - game->player.pos.y + (1
					- game->rc.step.y) / 2) / game->rc.raydir.y + 0.0001;
	else
		game->rc.perp_wall_dist = (game->rc.map.y - game->player.pos.x + (1
					- game->rc.step.x) / 2) / game->rc.raydir.x + 0.0001;
	game->rc.line_height = (int)(SCREEN_HEIGHT / game->rc.perp_wall_dist);
	game->rc.draw_start = (SCREEN_HEIGHT - game->rc.line_height) / 2;
	game->rc.draw_end = game->rc.line_height / 2 + SCREEN_HEIGHT / 2;


	
	// if (game->rc.draw_start < 0)
	// 	game->rc.draw_start = 0;
	// game->rc.draw_end = SCREEN_HEIGHT - game->rc.draw_start;
}

void	calculate_texture_coordinates(t_game *game)
{
	if (game->rc.side == 0)
		game->rc.wall_x = game->player.pos.x + game->rc.perp_wall_dist
			* game->rc.raydir.x;
	else
		game->rc.wall_x = game->player.pos.y + game->rc.perp_wall_dist
			* game->rc.raydir.y;
	game->rc.wall_x -= floor(game->rc.wall_x);
	game->rc.tex.x = game->rc.wall_x;
	if (game->rc.side == 0 && game->rc.raydir.y > 0)
		game->rc.tex.x = 1 - game->rc.tex.x ;
	if (game->rc.side == 1 && game->rc.raydir.x < 0)
		game->rc.tex.x = 1 - game->rc.tex.x;
	// game->rc.step_size = 1.0 * game->rc.texture->height / game->rc.line_height;
	// game->rc.tex_pos = (game->rc.draw_start - SCREEN_HEIGHT / 2
	// 		+ game->rc.line_height / 2) * game->rc.step_size;
}

void	print_stripes(t_game *game)
{
	int			y;
	int			x;
	int			wall_start;
	int			wall_end;
	t_wall		wall;
	t_texture	tex;

	tex.pos.y = wall.wall_y / wall.wall_height;
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		game->rc.texture = get_texture_directions(game);
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
		{
			render_walls(game, x, y);
		}
	}
}

// if (game->rc.draw_start < 0)
// 	wall_start = - game->rc.draw_start;
// else
// 	wall_start = game->rc.draw_start;
// if (game->rc.draw_end >= SCREEN_HEIGHT)
// 	wall_end = SCREEN_HEIGHT - 1;
// else
// 	wall_end = game->rc.draw_end;

void	set_ray_steps(t_game *game)
{
	game->rc.hit = 0;
	while (game->rc.hit == 0)
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
		if (game->map.grid[game->rc.map.x][game->rc.map.y] > '0')
			game->rc.hit = 1;
	}
}




