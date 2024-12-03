/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:01:09 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/03 18:07:04 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


/* 
 scale collor takes a color and a factor and returns a new color
 the new color is the old color with the factor applied to it
 factor is a double between 0 and 1
 */
unsigned int	scale_color(unsigned int color, double factor)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	red = red - (red * (factor / 1));
	green = green - (green * (factor / 1));
	blue = blue - (blue * (factor / 1));
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;
	return ((red << 16) | (green << 8) | blue);
}

int	get_color(t_vector current, t_vector start, t_vector end, t_vector delta)
{
	// int		red;
	int color;
	
	color = scale_color(COLOR_CYAN, 0.5);
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
	return (color);
}

int	parse_color(char *str)
{
	char	*temp;
	int		red;
	int		green;
	int		blue;

	temp = str;
	ft_skip_whitespace(&temp);
	red = ft_atoi(temp);
	temp = ft_strchr(temp, ',');
	temp++;
	green = ft_atoi(temp);
	temp = ft_strchr(temp, ',');
	temp++;
	blue = ft_atoi(temp);
	return ((red << 16) | (green << 8) | blue);
}