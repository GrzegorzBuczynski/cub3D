/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:01:09 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/10 17:40:44 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int	scale_color(int color, int i, int lines_per_step)
{
	int red = (color >> 16) & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = color & 0xFF;
	int factor = i * i;

	red = red - (red * factor / ((SCREEN_HEIGHT / 2) * (SCREEN_HEIGHT / 2)));
	green = green - (green * factor / ((SCREEN_HEIGHT / 2) * (SCREEN_HEIGHT / 2)));
	blue = blue - (blue * factor / ((SCREEN_HEIGHT / 2) * (SCREEN_HEIGHT / 2)));
	return ((red << 16) | (green << 8) | blue);
}

int get_color (int color, int i, bool scale)
{
	int lines_per_step;
	
	if (scale == false)
		return (color);
	lines_per_step = SCREEN_HEIGHT / 2;
	return (scale_color(color, i, lines_per_step));
}