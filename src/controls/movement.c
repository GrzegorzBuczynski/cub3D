/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:37:15 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/06 18:31:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_front(t_game *game)
{
	double	new_pos_y;
	double	new_pos_x;

	new_pos_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED
		* game->rc.time_ratio * game->params.speed_ratio;
	new_pos_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED
		* game->rc.time_ratio * game->params.speed_ratio;
	if (game->map.grid[(int)(new_pos_y + TO_WALL_DISTANCE
			* game->player.dir.y)][(int)game->player.pos.x] == '0'
		|| game->map.grid[(int)(new_pos_y + TO_WALL_DISTANCE
			* game->player.dir.y)][(int)game->player.pos.x] == 'O')
		game->player.pos.y = new_pos_y;
	if (game->map.grid[(int)game->player.pos.y][(int)(new_pos_x
		+ TO_WALL_DISTANCE * game->player.dir.x)] == '0'
		|| game->map.grid[(int)game->player.pos.y][(int)(new_pos_x
			+ TO_WALL_DISTANCE * game->player.dir.x)] == 'O')
		game->player.pos.x = new_pos_x;
}

void	move_back(t_game *game)
{
	double	new_pos_y;
	double	new_pos_x;

	new_pos_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED
		* game->rc.time_ratio * game->params.speed_ratio;
	new_pos_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED
		* game->rc.time_ratio * game->params.speed_ratio;
	if (game->map.grid[(int)(new_pos_y - TO_WALL_DISTANCE
			* game->player.dir.y)][(int)game->player.pos.x] == '0'
		|| game->map.grid[(int)(new_pos_y - TO_WALL_DISTANCE
			* game->player.dir.y)][(int)game->player.pos.x] == 'O')
		game->player.pos.y = new_pos_y;
	if (game->map.grid[(int)game->player.pos.y][(int)(new_pos_x
		- TO_WALL_DISTANCE * game->player.dir.x)] == '0'
		|| game->map.grid[(int)game->player.pos.y][(int)(new_pos_x
			- TO_WALL_DISTANCE * game->player.dir.x)] == 'O')
		game->player.pos.x = new_pos_x;
}

void	move_left(t_game *game)
{
	double	new_pos_y;
	double	new_pos_x;

	new_pos_y = game->player.pos.y - game->player.plane.y * MOVE_SPEED
		* game->rc.time_ratio * game->params.speed_ratio;
	new_pos_x = game->player.pos.x - game->player.plane.x * MOVE_SPEED
		* game->rc.time_ratio * game->params.speed_ratio;
	if (game->map.grid[(int)(new_pos_y - TO_WALL_DISTANCE
			* game->player.plane.y)][(int)game->player.pos.x] == '0'
		|| game->map.grid[(int)(new_pos_y - TO_WALL_DISTANCE
			* game->player.plane.y)][(int)game->player.pos.x] == 'O')
		game->player.pos.y = new_pos_y;
	if (game->map.grid[(int)game->player.pos.y][(int)(new_pos_x
		- TO_WALL_DISTANCE * game->player.plane.x)] == '0'
		|| game->map.grid[(int)game->player.pos.y][(int)(new_pos_x
			- TO_WALL_DISTANCE * game->player.plane.x)] == 'O')
		game->player.pos.x = new_pos_x;
}

void	move_right(t_game *game)
{
	double	new_pos_y;
	double	new_pos_x;

	new_pos_y = game->player.pos.y + game->player.plane.y * MOVE_SPEED
		* game->rc.time_ratio * game->params.speed_ratio;
	new_pos_x = game->player.pos.x + game->player.plane.x * MOVE_SPEED
		* game->rc.time_ratio * game->params.speed_ratio;
	if (game->map.grid[(int)(new_pos_y + TO_WALL_DISTANCE
			* game->player.plane.y)][(int)game->player.pos.x] == '0'
		|| game->map.grid[(int)(new_pos_y + TO_WALL_DISTANCE
			* game->player.plane.y)][(int)game->player.pos.x] == 'O')
		game->player.pos.y = new_pos_y;
	if (game->map.grid[(int)game->player.pos.y][(int)(new_pos_x
		+ TO_WALL_DISTANCE * game->player.plane.x)] == '0'
		|| game->map.grid[(int)game->player.pos.y][(int)(new_pos_x
			+ TO_WALL_DISTANCE * game->player.plane.x)] == 'O')
		game->player.pos.x = new_pos_x;
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
