/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:44:42 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 19:26:00 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	process_ray(t_game *game, int x, char c, t_wall *wall)
{
	set_wall_x(game, wall);
	set_distance(game, wall);
	set_wall_height(game, wall);
	set_draw_limits(game, wall);
	game->rc.tex_img = get_texture(game, c, game->rc.sec_part);
}

void	process_column(t_game *game, int x, char c)
{
	t_wall	wall;

	set_ray_direction(game, x);
	set_step_and_dist(game);
	if (scan_for_hit(game, c) == 0)
		return ;
	process_ray(game, x, c, &wall);
	draw_column(game, x, &wall);
}

void	draw_monster(t_game *game, char c)
{
	int	x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		process_column(game, x, c);
	}
}
