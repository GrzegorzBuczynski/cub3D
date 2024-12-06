/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:44:42 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/04 19:45:04 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void	draw_monster(t_game *game, char c)
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