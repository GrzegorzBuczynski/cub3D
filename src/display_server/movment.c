/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:37:15 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/25 18:48:14 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_front(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
	new_pos_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;
	if (game->map.map[(int)(new_pos_x + DISTANCE * game->player.dir.x)][(int)game->player.pos.y] == '0'
		|| game->map.map[(int)(new_pos_x + DISTANCE	* game->player.dir.x)][(int)game->player.pos.y] == 'O')
		game->player.pos.x = new_pos_x;
	if (game->map.map[(int)game->player.pos.x][(int)(new_pos_y + DISTANCE
		* game->player.dir.y)] == '0'
		|| game->map.map[(int)game->player.pos.x][(int)(new_pos_y + DISTANCE
			* game->player.dir.y)] == 'O')
		game->player.pos.y = new_pos_y;
}

void	move_back(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
	new_pos_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;
	if (game->map.map[(int)(new_pos_x - DISTANCE
			* game->player.dir.x)][(int)game->player.pos.y] == '0'
		|| game->map.map[(int)(new_pos_x - DISTANCE
			* game->player.dir.x)][(int)game->player.pos.y] == 'O')
		game->player.pos.x = new_pos_x;
	if (game->map.map[(int)game->player.pos.x][(int)(new_pos_y - DISTANCE
		* game->player.dir.y)] == '0'
		|| game->map.map[(int)game->player.pos.x][(int)(new_pos_y - DISTANCE
			* game->player.dir.y)] == 'O')
		game->player.pos.y = new_pos_y;
}

void	move_left(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos.x - game->player.plane.x * MOVE_SPEED;
	new_pos_y = game->player.pos.y - game->player.plane.y * MOVE_SPEED;
	if (game->map.map[(int)(new_pos_x - DISTANCE
			* game->player.plane.x)][(int)game->player.pos.y] == '0'
		|| game->map.map[(int)(new_pos_x - DISTANCE
			* game->player.plane.x)][(int)game->player.pos.y] == 'O')
		game->player.pos.x = new_pos_x;
	if (game->map.map[(int)game->player.pos.x][(int)(new_pos_y - DISTANCE
		* game->player.plane.y)] == '0'
		|| game->map.map[(int)game->player.pos.x][(int)(new_pos_y - DISTANCE
			* game->player.plane.y)] == 'O')
		game->player.pos.y = new_pos_y;
}

void	move_right(t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->player.pos.x + game->player.plane.x * MOVE_SPEED;
	new_pos_y = game->player.pos.y + game->player.plane.y * MOVE_SPEED;
	if (game->map.map[(int)(new_pos_x + DISTANCE
			* game->player.plane.x)][(int)game->player.pos.y] == '0'
		|| game->map.map[(int)(new_pos_x + DISTANCE
			* game->player.plane.x)][(int)game->player.pos.y] == 'O')
		game->player.pos.x = new_pos_x;
	if (game->map.map[(int)game->player.pos.x][(int)(new_pos_y + DISTANCE
		* game->player.plane.y)] == '0'
		|| game->map.map[(int)game->player.pos.x][(int)(new_pos_y + DISTANCE
			* game->player.plane.y)] == 'O')
		game->player.pos.y = new_pos_y;
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
		rotate_left(game);
	if (game->pressed.right)
		rotate_right(game);
	// if (game->pressed.space)
	// 	open_door_execute(game);
	return (true);
}