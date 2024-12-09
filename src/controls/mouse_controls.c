/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:24:47 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 17:00:00 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	mouse_press(int button, int x, int y, void *param)
{
	t_display	*display;

	display = (t_display *)param;
	(void)x;
	(void)y;
	/* 	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
			zoom(button, display);
		else */
	if (button == MOUSE_LEFT_BUTTON)
		display->mouse.is_pressed = true;
	return (0);
}

/*
** Handle mouse release
*/

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

/*
** Handle mouse move
*/

int	mouse_move(int x, int y, void *param)
{
	t_display	*display;

	display = (t_display *)param;
	display->mouse.previous_x = display->mouse.x;
	display->mouse.previous_y = display->mouse.y;
	display->mouse.x = x;
	display->mouse.y = y;
	if (display->mouse.is_pressed)
	{
		display->camera.beta += (x - display->mouse.previous_x) * 0.002;
		display->camera.alpha += (y - display->mouse.previous_y) * 0.002;
	}
	return (0);
}
