/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:01:09 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/13 19:54:08 by gbuczyns         ###   ########.fr       */
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
	int	red;
	int	green;
	int	blue;

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
	if (!temp)
		return (0);
	else
		temp++;
	green = ft_atoi(temp);
	temp = ft_strchr(temp, ',');
	if (!temp)
		return (0);
	else
		temp++;
	blue = ft_atoi(temp);
	return ((red << 16) | (green << 8) | blue);
}
