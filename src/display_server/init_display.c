/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:19:02 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/10 18:19:06 by gbuczyns         ###   ########.fr       */
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

void	draw(t_display *data)
{
	int	x;
	int	y;

	draw_background(data);
	y = 0;
	x = 0;
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// print_menu(fdf);
}

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
	display->img = mlx_new_image(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display->img)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->data_addr = mlx_get_data_addr(display->img,
			&(display->bits_per_pixel), &(display->size_line),
			&(display->endian));
	setup_controls(display);
	draw(display);
}

char	**memory(void)
{
	char	**array;

	array = calloc(sizeof(char **), 15);
	if (!array)
		return (NULL);
	array[0] = ft_strdup("        1111111111111111111111111\n");
	array[1] = ft_strdup("        1000000000110000000000001\n");
	array[2] = ft_strdup("        1011000001110000000000001\n");
	array[3] = ft_strdup("        1001000000000000000000001\n");
	array[4] = ft_strdup("111111111011000001110000000000001\n");
	array[5] = ft_strdup("1000000000110000011101111111111111111111\n");
	array[6] = ft_strdup("1111011111111101110000001000100000000001\n");
	array[7] = ft_strdup("1111011111111101110101001000111111111111\n");
	array[8] = ft_strdup("11000000110101011100000010001\n");
	array[9] = ft_strdup("1000000000000000110000001N0011\n");
	array[10] = ft_strdup("10000000000000001101010010001\n");
	array[11] = ft_strdup("110000011101010111110111100111\n");
	array[12] = ft_strdup("11110111111101011101111010001\n");
	array[13] = ft_strdup("11111111111111111111111111111\n");
	return (array);
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