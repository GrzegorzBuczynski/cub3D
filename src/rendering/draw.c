/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:24:23 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 18:44:01 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	put_pixel(t_image *image, int x, int y, unsigned int color)
{
	int	i;
	int	*data;

	data = (int *)(image->pixel_data);
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT && color != 0)
		data[y * SCREEN_WIDTH + x] = color;
}

void	put_pixel_with_black(t_image *img, int y, int x, unsigned int color)
{
	int				i;
	unsigned int	*image;

	image = (unsigned int *)(img->pixel_data);
	image[y * SCREEN_WIDTH + x] = color;
}

void	get_part_of_image(t_image *image, t_image *part, int x, int y)
{
	int	i;
	int	j;
	int	*part_img;
	int	*input_img;

	part_img = (int *)(part->pixel_data);
	input_img = (int *)(image->pixel_data);
	i = 0;
	while (i < part->height)
	{
		j = 0;
		while (j < part->width)
		{
			part_img[i * part->width + j] = input_img[(y + i) * image->width + x
				+ j];
			j++;
		}
		i++;
	}
}

void	put_image_to_image(t_display *display, t_image *image, int y, int x)
{
	int				i;
	int				j;
	int				*display_img;
	int				*input_img;
	unsigned int	b;

	display_img = (int *)(display->img.pixel_data);
	input_img = (int *)(image->pixel_data);
	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			b = input_img[i * image->width + j];
			if (input_img[i * image->width + j] != 0)
				display_img[(y + i) * SCREEN_WIDTH + x + j] = input_img[i
					* image->width + j];
			j++;
		}
		i++;
	}
}

t_image	cut_image(t_image *image, double factor, int width, int *data)
{
	t_image	cut;
	int		i;
	int		j;
	int		*input_data;

	cut.width = width;
	cut.height = image->height;
	cut.pixel_data = (char *)data;
	input_data = (int *)image->pixel_data;
	i = 1;
	while (i < cut.height)
	{
		j = 0;
		while (j < width)
		{
			data[i * width + j] = input_data[(int)(i * image->width + factor
					* image->width + j)];
			j++;
		}
		i++;
	}
	return (cut);
}

void	draw_square(t_image *image, t_vector pos, int size, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_with_black(image, pos.y + i, pos.x + j, color);
			j++;
		}
		i++;
	}
}
