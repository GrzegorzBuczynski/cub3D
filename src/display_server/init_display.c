/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:19:02 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/18 21:13:45 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	draw_background(t_display *data)
{
	int		*image;
	int		i;
	int		j;
	float	factor;
	int		color;

	ft_bzero(data->data_addr, SCREEN_WIDTH * SCREEN_HEIGHT
		* (data->bits_per_pixel / 8));
	image = (int *)(data->data_addr);
	i = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		factor = ((float)(i * i) / ((SCREEN_HEIGHT / 2.0) * (SCREEN_HEIGHT
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
		factor = ((float)((SCREEN_HEIGHT - i) * (SCREEN_HEIGHT - i))
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

void	draw(t_game *data)
{
	t_display	*display;

	display = &data->display;
	draw_background(display);
	print_walls(data);
	// draw_minimap(data);
	mlx_put_image_to_window(display->mlx, display->win, display->img, 0, 0);
	printf("tile.x: %d tile.y%d \n", data->player.tile.x, data->player.tile.y);
}

void	init_display(t_game *data)
{
	t_display	*display;

	display = &data->display;
	display->game = data;
	display->mlx = mlx_init();
	if (!display->mlx)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->win = mlx_new_window(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"display");
	if (!display->win)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->img = mlx_new_image(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display->img)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->data_addr = mlx_get_data_addr(display->img,
			&(display->bits_per_pixel), &(display->size_line),
			&(display->endian));
	data->a.buffer = (int *)(display->data_addr);
	setup_controls(display);
	draw(data);
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