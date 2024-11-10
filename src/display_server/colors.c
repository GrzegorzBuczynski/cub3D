/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:01:09 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/10 19:42:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	scale_color(int color, float factor)
{
	int	red;
	int	green;
	int	blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	red = red - (red * factor);
	green = green - (green * factor);
	blue = blue - (blue * factor);
	return ((red << 16) | (green << 8) | blue);
}

int	get_color(t_vector current, t_vector start, t_vector end, t_vector delta)
{
	// int		red;
	// int		green;
	// int		blue;
	// double	percentage;

	// if (current.color == end.color)
	// 	return (current.color);
	// if (delta.x > delta.y)
	// 	percentage = percent(start.x, end.x, current.x);
	// else
	// 	percentage = percent(start.y, end.y, current.y);
	// red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF,
	// 		percentage);
	// green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF,
	// 		percentage);
	// blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	// return ((red << 16) | (green << 8) | blue);
	return (COLOR_CYAN);
}