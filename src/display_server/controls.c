/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:36:32 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/13 15:36:34 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	close_program(void *param)
{
	t_display	*display;

	display = (t_display *)param;
	mlx_destroy_image(display->mlx, display->img);
	mlx_destroy_window(display->mlx, display->win);
	mlx_destroy_display(display->mlx);
	exit(0);
}

void	move(int key, t_game *game)
{
	if (key == ARROW_LEFT || key == K_A)
	{
		game->player.x -= game->player.step_x;
		if (game->player.x < 0
			&& game->map2.grid[game->player.tile.y][game->player.tile.x
			- 1] != '1')
		{
			game->player.tile.x--;
			game->player.x += 1;
		}
		else if (game->player.x < 0)
			game->player.x = 0;
	}
	else if (key == ARROW_UP || key == K_W)
	{
		game->player.tile.y--;
		game->player.pos.y -= 10;
	}
	else if (key == ARROW_RIGHT || key == K_D)
	{
		game->player.tile.x++;
		game->player.pos.x += 10;
	}
	else
	{
		game->player.tile.y++;
		game->player.pos.y += 10;
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
	if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP
		|| key == ARROW_DOWN, key == K_W || key == K_A || key == K_S
		|| key == K_D)
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
