/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:24:47 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/12 20:12:45 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	mouse_move(int x, int y, void *param)
{
	t_display	*display;
	t_mouse		*mouse;
	static int	i = 0;

	display = (t_display *)param;
	mouse = &display->mouse;
	mouse->delta_x = x - SCREEN_WIDTH / 2;
	mouse->delta_y = y - SCREEN_HEIGHT / 2;
	if (x != SCREEN_WIDTH / 2)
	{
		mlx_mouse_move(display->mlx, display->win, SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2);
		i++;
	}
	mouse->x = x;
	mouse->y = y;
	return (0);
}

void	update_mouse_move(t_game *game, int factor)
{
	t_mouse	mouse;

	mouse = game->display.mouse;
	game->rc.angle += (double)mouse.delta_x / SCREEN_WIDTH * factor * 2 * M_PI;
	if (game->rc.angle >= 2 * M_PI)
		game->rc.angle = game->rc.angle - 2 * M_PI;
	else if (game->rc.angle < 0)
		game->rc.angle = game->rc.angle + 2 * M_PI;
	update_dir_n_plane(game);
}

int	move(t_game *game)
{
	if (game->pressed.w)
		move_front(game);
	if (game->pressed.s)
		move_back(game);
	if (game->pressed.a)
		move_left(game);
	if (game->pressed.d)
		move_right(game);
	if (game->pressed.left)
		rotate_left(game, 1.0);
	if (game->pressed.right)
		rotate_right(game, 1.0);
	update_mouse_move(game, 1);
	return (true);
}
