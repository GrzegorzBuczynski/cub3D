/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:36:32 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/20 18:09:21 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

extern int	worldMap[mapWidth][mapHeight];

int	close_program(void *param)
{
	t_display	*display;

	display = (t_display *)param;
	mlx_destroy_image(display->mlx, display->img);
	mlx_destroy_window(display->mlx, display->win);
	mlx_destroy_display(display->mlx);
	exit(0);
}

void rotate_left(t_game *game)
{
	game->a.angle -= ROT_SPEED;
	if (game->a.angle < 0)
		game->a.angle += 360;
	game->a.playerdir.x = game->a.initial_playerdir *cos(game->a.angle * M_PI / 180);
	game->a.playerdir.y = game->a.initial_playerdir *sin(game->a.angle * M_PI / 180);
	game->a.plane.x = game->a.initial_plane *sin(game->a.angle * M_PI / 180);
	game->a.plane.y = game->a.initial_plane *cos(game->a.angle * M_PI / 180);
	
	game->player.step_side_side.x = STEP_SIZE * cos(game->a.angle * M_PI / 180);
	game->player.step_side_side.y = STEP_SIZE * sin(game->a.angle * M_PI / 180);
	game->player.step_top_down.x = STEP_SIZE * sin(game->a.angle * M_PI / 180);
	game->player.step_top_down.y = STEP_SIZE * cos(game->a.angle * M_PI / 180);
}

void rotate_right(t_game *game)
{
	game->a.angle += ROT_SPEED;
	if (game->a.angle >= 360)
		game->a.angle -= 360;
	game->a.playerdir.x = game->a.initial_playerdir *cos(game->a.angle * M_PI / 180);
	game->a.playerdir.y = game->a.initial_playerdir *sin(game->a.angle * M_PI / 180);
	game->a.plane.x = game->a.initial_plane *sin(game->a.angle * M_PI / 180);
	game->a.plane.y = game->a.initial_plane *cos(game->a.angle * M_PI / 180);
	
	game->player.step_side_side.x = STEP_SIZE * cos(game->a.angle * M_PI / 180);
	game->player.step_side_side.y = STEP_SIZE * sin(game->a.angle * M_PI / 180);
	game->player.step_top_down.x = -STEP_SIZE * sin(game->a.angle *	M_PI / 180);
	game->player.step_top_down.y = STEP_SIZE * cos(game->a.angle * M_PI / 180);
}

void walk_right(t_game *game)
{
	if (worldMap[(int)(game->player.pos.x + game->player.step_side_side.x)][(int)(game->player.pos.y)] == false)
		game->player.pos.x += game->player.step_side_side.x;
	if (worldMap[(int)(game->player.pos.x)][(int)(game->player.pos.y + game->player.step_side_side.y)] == false)
		game->player.pos.y += game->player.step_side_side.y;
}

void walk_left(t_game *game)
{
	if (worldMap[(int)(game->player.pos.x - game->player.step_side_side.x)][(int)(game->player.pos.y)] == false)
		game->player.pos.x -= game->player.step_side_side.x;
	if (worldMap[(int)(game->player.pos.x)][(int)(game->player.pos.y - game->player.step_side_side.y)] == false)
		game->player.pos.y -= game->player.step_side_side.y;
}

void walk_forward(t_game *game)
{
	if (worldMap[(int)(game->player.pos.x - game->player.step_top_down.x)][(int)(game->player.pos.y)] == false)
		game->player.pos.x -= game->player.step_top_down.x;
	if (worldMap[(int)(game->player.pos.x)][(int)(game->player.pos.y - game->player.step_top_down.y)] == false)
		game->player.pos.y -= game->player.step_top_down.y;
}

void walk_backward(t_game *game)
{
	if (worldMap[(int)(game->player.pos.x + game->player.step_top_down.x)][(int)(game->player.pos.y)] == false)
		game->player.pos.x += game->player.step_top_down.x;
	if (worldMap[(int)(game->player.pos.x)][(int)(game->player.pos.y + game->player.step_top_down.y)] == false)
		game->player.pos.y += game->player.step_top_down.y;
}

void	move(int key, t_game *game)
{
	if (key == ARROW_LEFT)
	{
		rotate_left(game);
	}
	else if (key == K_A )
	{
		walk_left(game);
	}
	else if (key == ARROW_UP || key == K_W)
	{
		walk_forward(game);
	}
	else if (key == ARROW_RIGHT)
	{
		rotate_right(game);
	}
	else if (key == K_D)
	{
		walk_right(game);
	}
	else if (key == ARROW_DOWN || key == K_S)
	{
		walk_backward(game);
	}
	draw(game);
}

void	rotate(int key, t_display *display)
{
	// if (key == NUM_PAD_2 || key == MAIN_PAD_2)
	// 	display->camera->alpha += 0.05;
	// else if (key == NUM_PAD_8 || key == MAIN_PAD_8)
	// 	display->camera->alpha -= 0.05;
	// else if (key == NUM_PAD_4 || key == MAIN_PAD_4)
	// 	display->camera->beta -= 0.05;
	// else if (key == NUM_PAD_6 || key == MAIN_PAD_6)
	// 	display->camera->beta += 0.05;
	// else if (key == NUM_PAD_1 || key == MAIN_PAD_1 || key == NUM_PAD_3
	// 	|| key == MAIN_PAD_3)
	// 	display->camera->gamma += 0.05;
	// else if (key == NUM_PAD_7 || key == MAIN_PAD_7 || key == NUM_PAD_9
	// 	|| key == MAIN_PAD_9)
	// 	display->camera->gamma -= 0.05;
	// draw(display, display);
}

int	key_press(int key, void *param)
{
	t_display	*display;

	display = (t_display *)param;
	if (key == MAIN_PAD_ESC)
		close_program(display);
	if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN || key == K_W || key == K_A || key == K_S || key == K_D)
		move(key, display->game);
	// if (key == NUM_PAD_PLUS || key == MAIN_PAD_PLUS || key == NUM_PAD_MINUS
	// 	|| key == MAIN_PAD_MINUS)
	// 	zoom(key, display);
	// else if (key == NUM_PAD_1 || key == MAIN_PAD_1 || key == NUM_PAD_2
	// 	|| key == MAIN_PAD_2 || key == NUM_PAD_3 || key == MAIN_PAD_3
	// 	|| key == NUM_PAD_4 || key == MAIN_PAD_4 || key == NUM_PAD_6
	// 	|| key == MAIN_PAD_6 || key == NUM_PAD_7 || key == MAIN_PAD_7
	// 	|| key == NUM_PAD_8 || key == MAIN_PAD_8 || key == NUM_PAD_9
	// 	|| key == MAIN_PAD_9)
	// 	rotate(key, display);
	// else if (key == MAIN_PAD_LESS || key == MAIN_PAD_MORE)
	// 	flatten(key, display);
	// else if (key == MAIN_PAD_P || key == MAIN_PAD_I)
	// 	change_projection(key, display);
	return (0);
}

void	setup_controls(t_display *data)
{
	mlx_hook(data->win, KEYPRESS, 1L, key_press, data);
	mlx_hook(data->win, DESTROYNOTIFY, (1L << 2), close_program, data);
	mlx_hook(data->win, BUTTONPRESS, (1L << 2), mouse_press, data);
	mlx_hook(data->win, BUTTONRELEASE, (1L << 3), mouse_release, data);
	mlx_hook(data->win, MOTIONNOTIFY, (1L << 6), mouse_move, data);
}
