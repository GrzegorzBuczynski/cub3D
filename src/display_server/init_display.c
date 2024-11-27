/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:19:02 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/27 19:54:46 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_display(t_game *game)
{
	t_display	*display;

	display = &game->display;
	display->game = game;
	display->mlx = mlx_init();
	if (!display->mlx)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->win = mlx_new_window(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"display");
	if (!display->win)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->mlx_img = mlx_new_image(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display->mlx_img)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->img.pixel_data = mlx_get_data_addr(display->mlx_img,
			&(display->img.bpp), &(display->img.line_length),
			&(display->img.endian));
	display->img.width = SCREEN_WIDTH;
	display->img.height = SCREEN_HEIGHT;
	game->rc.buffer = (int *)(display->img.pixel_data);
}

/* a * (i + 1) / a
gray_intensity = 0x40 - (0x40 * i / lines_per_step);
 */

// int			lines_per_step = SCREEN_HEIGHT / 2 / 40;

// static void	draw_background(t_display *data)
// {
// 	int	*image;
// 	int	i;
// 	int	j;
// 	int	lines_per_step;
// 	int	gray_intensity;
// 	int	color;

// 	lines_per_step = SCREEN_HEIGHT / 2;
// 	ft_bzero(data->data_addr, SCREEN_WIDTH * SCREEN_HEIGHT
// * (data->bits_per_pixel / 8));
// 	image = (int *)(data->data_addr);
// 	i = 0;

// 	// Draw ceiling with grayscale gradient (darkening)
// 	while (i < SCREEN_HEIGHT / 2)
// 	{
// 		gray_intensity = 0x40 - (0x40 * i / lines_per_step);
// Scale from mid-gray to black
// 		color = (gray_intensity << 16) | (gray_intensity << 8) | gray_intensity;
// Set R=G=B for gray
// 		j = 0;
// 		while (j < SCREEN_WIDTH)
// 		{
// 			image[i * SCREEN_WIDTH + j] = color;
// 			j++;
// 		}
// 		i++;
// 	}

// 	// Draw floor with grayscale gradient (brightening)
// 	while (i < SCREEN_HEIGHT)
// 	{
// 		gray_intensity = 0x40 + (0x40 * i / lines_per_step);
// Scale from dark to mid-gray
// 		color = (gray_intensity << 16) | (gray_intensity << 8) | gray_intensity;
// Set R=G=B for gray
// 		j = 0;
// 		while (j < SCREEN_WIDTH)
// 		{
// 			image[i * SCREEN_WIDTH + j] = color;
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void	draw_background(t_display *data)
// {
// 	int	*image;
// 	int	i;
// 	int	j;
// 	int	lines_per_step;
// 	int	gray_intensity;
// 	int	color;

// 	lines_per_step = SCREEN_HEIGHT / 2;
// 	ft_bzero(data->data_addr, SCREEN_WIDTH * SCREEN_HEIGHT
// (data->bits_per_pixel / 8));
// 	image = (int *)(data->data_addr);
// 	i = 0;

// 	// Draw ceiling with grayscale gradient
// 	while (i < SCREEN_HEIGHT / 2)
// 	{
// 		gray_intensity = 0x80 - (0x80 * i / lines_per_step);
// Scale intensity from 128 (0x80) to 0
// 		color = (gray_intensity << 16) | (gray_intensity << 8) | gray_intensity;
// Set R=G=B for gray
// 		j = 0;
// 		while (j < SCREEN_WIDTH)
// 		{
// 			image[i * SCREEN_WIDTH + j] = color;
// 			j++;
// 		}
// 		i++;
// 	}

// 	// Draw floor with solid gray color
// 	while (i < SCREEN_HEIGHT)
// 	{
// 		color = FLOOR;
// 		j = 0;
// 		while (j < SCREEN_WIDTH)
// 		{
// 			image[i * SCREEN_WIDTH + j] = color;
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void	draw_background(t_display *data)
// {
// 	int	*image;
// 	int	i;
// 	int	j;
// 	int	lines_per_step;
// 	int	color;

// 	lines_per_step = SCREEN_HEIGHT / 2 / 40;
// 	j = 0;
// 	ft_bzero(data->data_addr, SCREEN_WIDTH * SCREEN_HEIGHT
// 		* (data->bits_per_pixel / 8));
// 	image = (int *)(data->data_addr);
// 	i = 0;
// 	while (i < SCREEN_HEIGHT / 2)
// 	{
// 		color = CEILING - (0x020202 * i / lines_per_step);
// 		while (j < SCREEN_WIDTH)
// 		{
// 			image[i * SCREEN_WIDTH + j] = color;
// 			j++;
// 		}
// 		i++;
// 		j = 0;
// 	}
// 	while (i < SCREEN_HEIGHT)
// 	{
// 		color = CEILING - (0x020202 * i / lines_per_step);
// 		while (j < SCREEN_WIDTH)
// 		{
// 			image[i * SCREEN_WIDTH + j] = color;
// 			j++;
// 		}
// 		i++;
// 		j = 0;
// 	}
// }
// n = i / (SCREEN_HEIGHT * SCREEN_WIDTH / 40);
// printf("color: %x\n", CEILING - (0x020202 * n));
// image[i] = CEILING - (0x020202 * n);
// while (i < SCREEN_HEIGHT * SCREEN_WIDTH)
// {
// 	image[i] = FLOOR;
// 	i++;
// }