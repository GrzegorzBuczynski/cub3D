/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/13 20:29:28 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	update_raycasting_params(t_game *game)
{
	if (game->rc.lenght_to.y < game->rc.lenght_to.x)
	{
		game->rc.lenght_to.y += game->rc.delta_dist.y;
		game->rc.map.y += game->rc.step.y;
		game->rc.side = 0;
	}
	else
	{
		game->rc.lenght_to.x += game->rc.delta_dist.x;
		game->rc.map.x += game->rc.step.x;
		game->rc.side = 1;
	}
}

int	scan_for_hit(t_game *game, char c)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		update_raycasting_params(game);
		if (game->map.grid[game->rc.map.y][game->rc.map.x] == c)
		{
			hit = 1;
			return (1);
		}
		else if (game->map.grid[game->rc.map.y][game->rc.map.x] == '1')
		{
			hit = 1;
			return (0);
		}
	}
	return (0);
}

void	render_wall_slice(t_game *game, int x, t_wall *wall)
{
	int				y;
	unsigned int	color;

	y = game->rc.draw_start - 1;
	while (++y < game->rc.draw_end)
	{
		wall->factor.y = ((double)y - wall->y_start) / wall->height;
		color = get_texture_pixel(game->rc.tex_img, wall->factor.y,
				wall->factor.x);
		color = scale_color(color, wall->perp_wall_dist / 30);
		put_pixel(&game->display.img, x, y, color);
	}
}

void	process_column(t_game *game, int x, char c, t_wall *wall)
{
	set_ray_direction(game, x);
	set_step_and_dist(game);
	if (scan_for_hit(game, c) == 0)
		return ;
	set_wall_x(game, wall);
	set_distance(game, wall);
	set_wall_height(wall);
	set_draw_limits(game, wall);
	game->rc.tex_img = get_texture(game, c, game->rc.sec_part);
	render_wall_slice(game, x, wall);
}

void	draw_object(t_game *game, char c)
{
	int		x;
	t_wall	wall;

	x = -1;
	ft_bzero(&wall, sizeof(t_wall));
	while (++x < SCREEN_WIDTH)
		process_column(game, x, c, &wall);
}
