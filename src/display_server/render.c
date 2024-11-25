/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:43:07 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/25 20:37:29 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_background(t_display *data)
{
	int		*image;
	int		i;
	int		j;
	double	factor;
	int		color;

	ft_bzero(data->data_addr, SCREEN_WIDTH * SCREEN_HEIGHT
		* (data->bits_per_pixel / 8));
	image = (int *)(data->data_addr);
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
	game->rc.tex.y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
	game->rc.tex_pos += game->rc.step_size;
	game->rc.color = get_texture_pixel(get_texture_directions(game),
			game->rc.tex_x, game->rc.tex.y);
	my_mlx_pixel_put(game->back, x, y, game->rc.color);
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
		calculate_texture_coordinates(game);
		y = game->rc.draw_start - 1;
		while (++y < game->rc.draw_end)
		{
			render_walls(game, x, y);
		}
	}
}

void	draw(t_game *game)
{
	t_display	*display;

	display = &game->display;
	draw_background(display);
	print_walls(game);
	// draw_minimap(data);
	move(game);
	mlx_put_image_to_window(display->mlx, display->win, display->img, 0, 0);
}