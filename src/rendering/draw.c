/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:24:23 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/02 18:42:35 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void put_pixel(t_display *display, int x, int y, unsigned int color)
{
	int i;
	int *image;

	image = (int *)(display->img.pixel_data);
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		image[y * SCREEN_WIDTH + x] = color;
}

static void estimate_delta(t_vector s, t_vector f, t_vector *delta)
{
	delta->x = ft_abs(s.x - f.x);
	delta->y = ft_abs(s.y - f.y);
}

static void calculate_sign(t_vector s, t_vector f, t_vector *sign)
{
	if (f.x < s.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (f.y < s.y)
		sign->y = 1;
	else
		sign->y = -1;
}

void draw_line(t_line *line, t_display *data)
{
	t_vector delta;
	t_vector sign;
	t_vector cur;
	int error[2];

	estimate_delta(line->s, line->f, &delta);
	calculate_sign(line->s, line->f, &sign);
	error[0] = delta.x - delta.y;
	cur = line->f;
	while (cur.x != line->s.x || cur.y != line->s.y)
	{
		put_pixel(data, cur.x, cur.y, line->color);
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}



void get_part_of_image(t_image *image, t_image *part, int x, int y)
{
	int i;
	int j;
	int *part_img;
	int *input_img;

	part_img = (int *)(part->pixel_data);
	input_img = (int *)(image->pixel_data);
	i = 0;
	while (i < part->height)
	{
		j = 0;
		while (j < part->width)
		{
			part_img[i * part->width + j] = input_img[(y + i) * image->width + x + j];
			j++;
		}
		i++;
	}
}

// function takes display, image to put and x, y coordinates where to put image
void put_image_to_image(t_display *display, t_image *image, int y, int x)
{
	int i;
	int j;
	int *display_img;
	int *input_img;

	display_img = (int *)(display->img.pixel_data);
	input_img = (int *)(image->pixel_data);
	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			unsigned int b = input_img[i * image->width + j];
			if (input_img[i * image->width + j] != 0)
				display_img[(y + i) * SCREEN_WIDTH + x + j] = input_img[i * image->width + j];
			j++;
		}
		i++;
	}
}

t_image cut_image(t_image *image, double factor, int width)
{
	t_image cut;
	int i;
	int j;
	int *input_img;
	int *cut_img;

	cut.width = width;
	cut.height = image->height;
	cut.pixel_data = ft_calloc(sizeof(int) * cut.width * cut.height, 1);
	input_img = (int *)(image->pixel_data);
	cut_img = (int *)(cut.pixel_data);
	i = 1;
	while (i < cut.height)
	{
		j = 0;
		while (j < width)
		{
			cut_img[i * width + j] = input_img[(int)(i * image->width + factor * image->width + j)];
			j++;
		}
		i++;
	}
	return (cut);
}

// // function takes display, image to put and x, y coordinates where to put image
// void put_frame_to_image(t_display *display, t_image *image, int x, int y, double factor, int width)
// {
// 	int i;
// 	int j;
// 	int *display_img;
// 	int *input_img;

// 	display_img = (int *)(display->display_img.pixel_data);
// 	input_img = (int *)(image->pixel_data);
// 	i = 0;
// 	while (i < image->height)
// 	{
// 		j = 0;
// 		while (j < image->width)
// 		{
// 			if (input_img[i * image->width + j] != 0)
// 			{
// 				if (j < width || j > image->width - width || i < width || i > image->height - width)
// 					display_img[(y + i) * SCREEN_WIDTH + x + j] = input_img[i * image->width + j];
// 				else
// 					display_img[(y + i) * SCREEN_WIDTH + x + j] = input_img[i * image->width + j] * factor;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
