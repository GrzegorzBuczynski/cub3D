/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:43:07 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/01 18:30:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_background(t_display *display)
{
	int		*image;
	int		i;
	int		j;
	double	factor;
	int		color;

	ft_bzero(display->img.pixel_data, SCREEN_WIDTH * SCREEN_HEIGHT
		* (display->img.bpp / 8));
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
			image[i * SCREEN_WIDTH + j] = color;
			j++;
		}
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		factor = ((double)((SCREEN_HEIGHT - i) * (SCREEN_HEIGHT - i))
				/ ((SCREEN_HEIGHT / 2.0) * (SCREEN_HEIGHT / 2.0)));
		color = scale_color(FLOOR, factor);
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			image[i * SCREEN_WIDTH + j] = color;
			j++;
		}
		i++;
	}
}

static void	render_walls(t_game *game, int x, int y)
{
	game->rc.tex.y = (int)game->rc.tex_pos & (game->rc.texture->height - 1);
	game->rc.tex_pos += game->rc.step_size;
	game->rc.color = get_texture_pixel(game->rc.texture, game->rc.tex.x,
			game->rc.tex.y);
	if (game->rc.scale_color)
		game->rc.color = scale_color(game->rc.color, game->rc.perp_wall_dist
				/ 40);
	put_pixel(&game->display, x, y, game->rc.color);
	// my_mlx_pixel_put(&game->display.img, x, y, game->rc.color);
}

void	print_walls(t_game *game)
{
	int	y;
	int	x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray_direction_calculate(game, x);
		calculate_step_and_dist(game);
		set_ray_steps(game);
		calculate_wall_parameters(game);
		game->rc.texture = get_texture_directions(game);
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
		{
			render_walls(game, x, y);
		}
	}
}

void	limit_fps(t_game *game)
{
	unsigned int	delay_time;

	if (game->params.limit_fps)
	{
		delay_time = 1000 / game->params.fps;
		ft_sleep(game->time.old_time, 1000 / FPS);
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

int	draw(t_game *game)
{
	t_display	*display;
	void		*mlx_img;

	display = &game->display;
	draw_background(display);
	print_walls(game);
	render_compass(game);
	move(game);
	mlx_put_image_to_window(display->mlx, display->win, display->mlx_img, 0, 0);
	limit_fps(game);
	game->time.new_time = get_time();
	game->time.frame_time = game->time.new_time - game->time.old_time;
	game->time.old_time = game->time.new_time;
	// // Print FPS for debugging
	fps_counter(game, (int)game->time.frame_time);
	printf("fps: %f\n", 1000.0 / game->time.frame_time);
	return (0);
}
