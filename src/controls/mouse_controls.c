/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:24:47 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/06 18:22:45 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	mouse_press(int button, int x, int y, void *param)
{
	t_display	*display;

	display = (t_display *)param;
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT_BUTTON)
		display->mouse.is_pressed = true;
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_display	*display;

	(void)x;
	(void)y;
	(void)button;
	display = (t_display *)param;
	display->mouse.is_pressed = false;
	return (0);
}

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
