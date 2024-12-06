/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:43:55 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/04 13:26:11 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

#define POWER 7

static void	draw_ceiling(unsigned int color, t_display *display)
{
	int				*image;
	int				i;
	int				j;
	double			factor;
	unsigned int	color_base;

	image = (int *)(display->img.pixel_data);
	color_base = color;
	i = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		factor = ((double)pow(i, POWER) / pow(SCREEN_HEIGHT/2, POWER));
		color_base = scale_color(color, factor);
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			image[i * SCREEN_WIDTH + j] = color_base;
			j++;
		}
		i++;
	}
}

static void	draw_floor(unsigned int color, t_display *display)
{
	int				*image;
	int				i;
	int				j;
	double			factor;
	unsigned int	color_base;

	image = (int *)(display->img.pixel_data);
	color_base = color;
	i = SCREEN_HEIGHT;
	while (i > SCREEN_HEIGHT / 2 - 1)
	{
		factor = ((double)pow((SCREEN_HEIGHT - 1 - i), POWER) / pow(SCREEN_HEIGHT
					/ 2, POWER));
		color_base = scale_color(color, factor);
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			image[i * SCREEN_WIDTH + j] = color_base;
			j++;
		}
		i--;
	}
}

void	draw_background(t_game *game, t_display *display)
{
	draw_ceiling(game->map.ceiling, display);
	draw_floor(game->map.floor, display);
}

void	limit_fps(t_game *game)
{
	unsigned int	delay_time;

	if (game->params.limit_fps)
	{
		delay_time = 1000 / game->params.fps;
		ft_sleep(game->time.start_time, delay_time);
	}
}