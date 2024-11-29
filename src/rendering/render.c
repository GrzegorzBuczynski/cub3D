/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:43:07 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/29 20:45:50 by gbuczyns         ###   ########.fr       */
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

	ft_bzero(display->img.pixel_data, SCREEN_WIDTH * SCREEN_HEIGHT * (display->img.bpp
			/ 8));
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
	game->rc.color = get_texture_pixel(game->rc.texture,
			game->rc.tex.x, game->rc.tex.y);
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

int	draw(t_game *game)
{
	t_display *display;
	void *mlx_img;
	int width;
	int height;
	char *data;

	display = &game->display;
	draw_background(display);
	// mlx_img = mlx_xpm_file_to_image(display->mlx, "./textures/walls2/wallE.xpm", &width,
	// 		&height);

	// image.pixel_data = mlx_get_data_addr(mlx_img, &image.bpp, &image.width, &image.endian);

	// image.pixel_data = mlx_get_data_addr(mlx_img, image.bpp, &image.width, &image.endian);
	// data = (game->map.no.pixel_data);
	// for(int i = 0; i < game->map.no.width * game->map.no.height*4; i++)
	// {
	// 	char *c = (char *)&data[i];
	// 	display->img.pixel_data[i] = data[i];
	// }
	// mlx_put_image_to_window(display->mlx, display->win, mlx_img, 0, 0);
	
	print_walls(game);
	// draw_minimap(data);
	move(game);
	mlx_put_image_to_window(display->mlx, display->win, display->mlx_img, 0, 0);
	game->time.new_time = get_time();
	game->time.frame_time = game->time.new_time - game->time.old_time;
	game->time.old_time = game->time.new_time;
	printf("fps: %f\n", 1000 / game->time.frame_time);
	// printf("pos.x: %f pos.y%f angle %f player.dir.x: %f playerdir.y %f planedir.x %f planedir.y %f\n", game->player.pos.x, game->player.pos.y, game->rc.angle, game->player.dir.x, game->player.dir.y, game->player.plane.y, game->player.plane.x);
	return (0);
}