/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:24:23 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/10 22:02:48 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	put_pixel(t_display *display, int x, int y, int color)
{
	int	i;
	int *image;

	image = (int *)(display->data_addr);
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		image[y * SCREEN_WIDTH + x] = color;
}


static void	estimate_delta(t_vector s, t_vector f, t_vector *delta)
{
	delta->x = ft_abs(s.x - f.x);
	delta->y = ft_abs(s.y - f.y);
}

static void	calculate_sign(t_vector s, t_vector f, t_vector *sign)
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

void	draw_line(t_line *line, t_display *data)
{
	t_vector	delta;
	t_vector	sign;
	t_vector	cur;
	int		error[2];

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

// void	draw_line(t_vector f, t_vector s, t_display *data)
// {
// 	t_vector	delta;
// 	t_vector	sign;
// 	t_vector	cur;
// 	int		error[2];

// 	estimate_delta(s, f, &delta);
// 	calculate_sign(s, f, &sign);
// 	error[0] = delta.x - delta.y;
// 	cur = f;
// 	while (cur.x != s.x || cur.y != s.y)
// 	{
// 		put_pixel(data, cur.x, cur.y, get_color(cur, f, s, delta));
// 		error[1] = error[0] * 2;
// 		if (error[1] > -delta.y)
// 		{
// 			error[0] -= delta.y;
// 			cur.x += sign.x;
// 		}
// 		if (error[1] < delta.x)
// 		{
// 			error[0] += delta.x;
// 			cur.y += sign.y;
// 		}
// 	}
// }