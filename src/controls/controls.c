/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:36:32 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/01 18:07:06 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

extern int	worldMap[mapWidth][mapHeight];

int	close_program(void *param)
{
	t_display	*display;

	display = (t_display *)param;
	mlx_destroy_image(display->mlx, display->mlx_img);
	mlx_destroy_window(display->mlx, display->win);
	mlx_destroy_display(display->mlx);
	exit(0);
}

static int	key_hook(int keycode, t_game *game)
{
	if (keycode == K_W || keycode == ARROW_UP)
		game->pressed.w = true;
	if (keycode == K_S || keycode == ARROW_DOWN)
		game->pressed.s = true;
	if (keycode == K_A)
		game->pressed.a = true;
	if (keycode == K_D)
		game->pressed.d = true;
	if (keycode == ARROW_RIGHT)
		game->pressed.right = true;
	if (keycode == ARROW_LEFT)
		game->pressed.left = true;
	// if (keycode == SHIFT)
	// 	game->pressed.left = true;
	// if (keycode == KEY_SPACE)
	// 	game->pressed.space = true;
	return (0);
}

void activate(t_game *game)
{
	game->pressed.w = true;
	game->pressed.s = true;
	game->pressed.a = true;
	game->pressed.d = true;
	game->pressed.right = true;
	game->pressed.left = true;
}

int	key_release_hook(int keycode, t_game *game)
{
	if ((keycode == K_W ||keycode == ARROW_UP)  && game->pressed.w)
		game->pressed.w = false;
	if ((keycode == K_S || keycode == ARROW_DOWN) && game->pressed.s)
		game->pressed.s = false;
	if (keycode == K_A && game->pressed.a)
		game->pressed.a = false;
	if (keycode == K_D && game->pressed.d)
		game->pressed.d = false;
	if (keycode == ARROW_RIGHT && game->pressed.right)
		game->pressed.right = false;
	if (keycode == ARROW_LEFT && game->pressed.left)
		game->pressed.left = false;
	// if (keycode == SHIFT && game->pressed.shift)
	// 	game->pressed.shift = false;
	return (0);
}

int	key_press(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == MAIN_PAD_ESC)
		close_program(&game->display);
	if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN || key == K_W || key == K_A || key == K_S || key == K_D)
		key_hook(key, game);
	return (0);
}

void	setup_controls(t_game *game)
{
	t_display *display;

	display = &game->display;
	mlx_hook(display->win, KEYPRESS, KEYPRESSMASK, key_press, game);
	mlx_hook(display->win, KEYRELEASE, KEYRELEASEMASK, key_release_hook, game);
	mlx_hook(display->win, DESTROYNOTIFY, (1L << 2), close_program, display);
	mlx_hook(display->win, BUTTONPRESS, (1L << 2), mouse_press, display);
	mlx_hook(display->win, BUTTONRELEASE, (1L << 3), mouse_release, display);
	mlx_hook(display->win, MOTIONNOTIFY, (1L << 6), mouse_move, display);
}



// void	rotate(int key, t_display *display)
// {
// 	// if (key == NUM_PAD_2 || key == MAIN_PAD_2)
// 	// 	display->camera->alpha += 0.05;
// 	// else if (key == NUM_PAD_8 || key == MAIN_PAD_8)
// 	// 	display->camera->alpha -= 0.05;
// 	// else if (key == NUM_PAD_4 || key == MAIN_PAD_4)
// 	// 	display->camera->beta -= 0.05;
// 	// else if (key == NUM_PAD_6 || key == MAIN_PAD_6)
// 	// 	display->camera->beta += 0.05;
// 	// else if (key == NUM_PAD_1 || key == MAIN_PAD_1 || key == NUM_PAD_3
// 	// 	|| key == MAIN_PAD_3)
// 	// 	display->camera->gamma += 0.05;
// 	// else if (key == NUM_PAD_7 || key == MAIN_PAD_7 || key == NUM_PAD_9
// 	// 	|| key == MAIN_PAD_9)
// 	// 	display->camera->gamma -= 0.05;
// 	// draw(display, display);
// }


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



	// void update_playerdir(t_game *game)
// {
// 	game->rc.playerdir.x = game->rc.initial_playerdir * sin(game->rc.angle * M_PI / 180);
// 	game->rc.playerdir.y = game->rc.initial_playerdir * cos(game->rc.angle * M_PI / 180);
// }

// void update_plane(t_game *game)
// {
// 	game->rc.plane.x = game->rc.initial_plane *cos(game->rc.angle * M_PI / 180);
// 	game->rc.plane.y = game->rc.initial_plane *sin(game->rc.angle * M_PI / 180);
// }

// void decrement_angle(t_game *game)
// {
// 	game->rc.angle -= ROT_SPEED;
// 	if (game->rc.angle < 0)
// 		game->rc.angle += 360;
// }

// void increment_angle(t_game *game)
// {
// 	game->rc.angle += ROT_SPEED;
// 	if (game->rc.angle >= 360)
// 		game->rc.angle -= 360;
// }

// void update_step(t_game *game)
// {
// 	game->player.step_side_side.x = STEP_SIZE * cos(game->rc.angle * M_PI / 180);
// 	game->player.step_side_side.y = STEP_SIZE * sin(game->rc.angle * M_PI / 180);
// 	game->player.step_top_down.x = STEP_SIZE * sin(game->rc.angle * M_PI / 180);
// 	game->player.step_top_down.y = STEP_SIZE * cos(game->rc.angle * M_PI / 180);
	
// };



// void walk_right(t_game *game)
// {
// 	if (worldMap[(int)(game->player.pos.x + game->player.step_side_side.x)][(int)(game->player.pos.y)] == false)
// 		game->player.pos.x += game->player.step_side_side.x;
// 	if (worldMap[(int)(game->player.pos.x)][(int)(game->player.pos.y + game->player.step_side_side.y)] == false)
// 		game->player.pos.y += game->player.step_side_side.y;
// }

// void walk_left(t_game *game)
// {
// 	if (worldMap[(int)(game->player.pos.x - game->player.step_side_side.x)][(int)(game->player.pos.y)] == false)
// 		game->player.pos.x -= game->player.step_side_side.x;
// 	if (worldMap[(int)(game->player.pos.x)][(int)(game->player.pos.y - game->player.step_side_side.y)] == false)
// 		game->player.pos.y -= game->player.step_side_side.y;
// }

// void walk_forward(t_game *game)
// {
// 	if (worldMap[(int)(game->player.pos.x - game->player.step_top_down.x)][(int)(game->player.pos.y)] == false)
// 		game->player.pos.x -= game->player.step_top_down.x;
// 	if (worldMap[(int)(game->player.pos.x)][(int)(game->player.pos.y - game->player.step_top_down.y)] == false)
// 		game->player.pos.y -= game->player.step_top_down.y;
// }

// void walk_backward(t_game *game)
// {
// 	if (worldMap[(int)(game->player.pos.x + game->player.step_top_down.x)][(int)(game->player.pos.y)] == false)
// 		game->player.pos.x += game->player.step_top_down.x;
// 	if (worldMap[(int)(game->player.pos.x)][(int)(game->player.pos.y + game->player.step_top_down.y)] == false)
// 		game->player.pos.y += game->player.step_top_down.y;
// }


// void	move(int key, t_game *game)
// {
// 	if (key == ARROW_LEFT)
// 	{
// 		rotate_left(game);
// 	}
// 	else if (key == K_A )
// 	{
// 		walk_left(game);
// 	}
// 	else if (key == ARROW_UP || key == K_W)
// 	{
// 		walk_forward(game);
// 	}
// 	else if (key == ARROW_RIGHT)
// 	{
// 		rotate_right(game);
// 	}
// 	else if (key == K_D)
// 	{
// 		walk_right(game);
// 	}
// 	else if (key == ARROW_DOWN || key == K_S)
// 	{
// 		walk_backward(game);
// 	}
// }
