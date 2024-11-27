/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:43:07 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/27 19:42:37 by gbuczyns         ###   ########.fr       */
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

	ft_bzero(data->img.pixel_data, SCREEN_WIDTH * SCREEN_HEIGHT * (data->img.bpp
			/ 8));
	image = (int *)(data->img.pixel_data);
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
	game->rc.color = get_texture_pixel(game->rc.texture,
			game->rc.tex_x, game->rc.tex.y);
	my_mlx_pixel_put(&game->display.img, x, y, game->rc.color);
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

int	draw(t_game *game)
{
	t_display *display;

	display = &game->display;
	draw_background(display);
	print_walls(game);
	// draw_minimap(data);
	move(game);
	mlx_put_image_to_window(display->mlx, display->win, display->mlx_img, 0, 0);
	printf("pos.x: %f pos.y%f angle %f playerdir.x: %f playerdir.y %f planedir.x %f planedir.y %f\n", game->player.pos.x, game->player.pos.y, game->rc.angle, game->rc.playerdir.x, game->rc.playerdir.y, game->rc.plane.x, game->rc.plane.y);
	return (0);
}