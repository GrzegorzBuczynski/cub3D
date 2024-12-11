/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:36:32 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/09 20:18:51 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	close_program(void *param)
{
	t_display	*display;

	display = (t_display *)param;
	mlx_destroy_image(display->mlx, display->mlx_img);
	mlx_destroy_window(display->mlx, display->win);
	mlx_destroy_display(display->mlx);
	gexit(0);
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == MAIN_PAD_ESC)
		close_program(&game->display);
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
	if (keycode == K_SPACE)
		game->params.speed_ratio = 2;
	return (0);
}

void	activate(t_game *game)
{
	game->pressed.w = true;
	game->pressed.s = true;
	game->pressed.a = true;
	game->pressed.d = true;
	game->pressed.right = true;
	game->pressed.left = true;
}

int	key_release(int keycode, t_game *game)
{
	if ((keycode == K_W || keycode == ARROW_UP) && game->pressed.w)
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
	if (keycode == K_SPACE)
		game->params.speed_ratio = 1;
	return (0);
}

void	setup_controls(t_game *game)
{
	t_display	*display;

	display = &game->display;
	mlx_hook(display->win, KEYPRESS, KEYPRESSMASK, key_press, game);
	mlx_hook(display->win, KEYRELEASE, KEYRELEASEMASK, key_release, game);
	mlx_hook(display->win, DESTROYNOTIFY, (1L << 2), close_program, display);
	mlx_hook(display->win, BUTTONPRESS, (1L << 2), mouse_press, display);
	mlx_hook(display->win, BUTTONRELEASE, (1L << 3), mouse_release, display);
	mlx_hook(display->win, MOTIONNOTIFY, (1L << 6), mouse_move, display);
}
