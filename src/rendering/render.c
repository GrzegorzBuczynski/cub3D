/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:43:07 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/03 21:49:14 by gbuczyns         ###   ########.fr       */
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
	while (i > SCREEN_HEIGHT / 2)
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
		ft_sleep(game->time.old_time, 1000 / game->params.fps);
	}
}

void	fps_counter(t_game *game, int frame_time)
{
	static int	i = 0;
	static int	arr[20] = {0};
	int			avg;
	int			fps;

	avg = 0;
	fps = 1000 / frame_time; // Obliczanie FPS na podstawie czasu klatki.
	arr[i] = fps;            // Przypisanie bieżącego FPS do tablicy.
	i = (i + 1) % 20;        // Cycliczny wskaźnik do tablicy.
	// Obliczanie średniej FPS.
	for (int j = 0; j < 20; j++)
		avg += arr[j];
	avg /= 20;
	mlx_string_put(game->display.mlx, game->display.win, 1315, 30, 0xFFFFFF,
		"FPS: ");
	mlx_string_put(game->display.mlx, game->display.win, 1350, 30, 0xFFFFFF,
		ft_itoa(avg));
}

void	set_times(t_game *game)
{
	game->time.new_time = get_time();
	game->time.frame_time = game->time.new_time - game->time.old_time;
	game->time.old_time = game->time.new_time;
	fps_counter(game, (int)game->time.frame_time);
	game->rc.time_ratio = game->time.frame_time / 16.0;
}

void	debug(t_game *game)
{
	printf("pos.y %d pox.x %d \n", (int)game->player.pos.y,
		(int)game->player.pos.x);
	printf("fps: %f\n", 1000.0 / game->time.frame_time);
	printf("pos.x: %f pos.y%f angle %f player.dir.x:"
			"%f playerdir.y	%f planedir.x %f planedir.y %f\n",
			game->player.pos.x,
			game->player.pos.y,
			game->rc.angle,
			game->player.dir.x,
			game->player.dir.y,
			game->player.plane.y,
			game->player.plane.x);
}

int	draw(t_game *game)
{
	t_display	*display;
	void		*mlx_img;

	display = &game->display;
	draw_background(game, display);
	print_walls(game);
	render_compass(game);
	draw_minimap(game);
	mlx_put_image_to_window(display->mlx, display->win, display->mlx_img, 0, 0);
	limit_fps(game);
	set_times(game);
	move(game);
	// debug(game);
	return (0);
}

/*
static void	draw_ceiling(t_display *display, double jump_factor)
{
	int		*image;
	int		i;
	int		j;
	double	factor;
	int		color;

	image = (int *)(display->img.pixel_data);
	i = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		factor = ((double)(i * i) / ((SCREEN_HEIGHT / 2.0) * (SCREEN_HEIGHT
						/ 2.0)));
		color = scale_color(CEILING, factor);
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			image[(int)((i + jump_factor) * SCREEN_WIDTH + j)] = color;
			j++;
		}
		i++;
	}
}

static void	draw_floor(t_display *display, double jump_factor)
{
	int		*image;
	int		i;
	int		j;
	double	factor;
	int		color;

	image = (int *)(display->img.pixel_data);
	i = SCREEN_HEIGHT / 2;
	while (i < SCREEN_HEIGHT)
	{
		factor = ((double)((SCREEN_HEIGHT - i) * (SCREEN_HEIGHT - i))
				/ ((SCREEN_HEIGHT / 2.0) * (SCREEN_HEIGHT / 2.0)));
		color = scale_color(FLOOR, factor);
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			image[(int)((i + jump_factor) * SCREEN_WIDTH + j)] = color;
			j++;
		}
		i++;
	}
}

void	draw_background(t_game *game)
{
	int			i;
	double		factor;
	double		jump_factor;
	t_display	*display;

	jump_factor = 0;
	display = &game->display;
	i = 0;
	if (game->params.jump)
	{
		if (i < 30 * game->rc.time_ratio)
		{
			factor = 0.5 + ((double)(i * i) / (30.0 * 30.0));
			jump_factor = factor * 10;
				// Adjust the multiplier as needed for the jump effect
		}
		else if (i < 60 * game->rc.time_ratio)
		{
			factor = 1.0 - ((double)(i - 30) * (i - 30) / (30.0 * 30.0));
			jump_factor = factor * 10;
				// Adjust the multiplier as needed for the jump effect
		}
		i++;
		if (i == 60 * game->rc.time_ratio)
		{
			game->params.jump = 0;
			i = 0;
		}
	}
	draw_ceiling(display, jump_factor);
	draw_floor(display, jump_factor);
}
 */
