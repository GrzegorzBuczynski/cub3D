/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:03:09 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/09 19:03:11 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

static void	draw_thick_point(t_image *image, t_vector cur, int thickness,
		int color)
{
	int	i;
	int	j;

	i = -thickness / 2;
	while (i <= thickness / 2)
	{
		j = -thickness / 2;
		while (j <= thickness / 2)
		{
			put_pixel(image, cur.x + i, cur.y + j, color);
			j++;
		}
		i++;
	}
}

static void	update_error_and_position(t_vector *cur, t_vector sign,
		t_vector delta, int *error)
{
	int	error2;

	error2 = error[0] * 2;
	if (error2 > -delta.y)
	{
		error[0] -= delta.y;
		cur->x += sign.x;
	}
	if (error2 < delta.x)
	{
		error[0] += delta.x;
		cur->y += sign.y;
	}
}

void	draw_line(t_line *line, t_image *image)
{
	int			error[2];
	t_vector	delta;
	t_vector	sign;
	t_vector	cur;

	estimate_delta(line->s, line->f, &delta);
	calculate_sign(line->s, line->f, &sign);
	error[0] = delta.x - delta.y;
	cur = line->f;
	while (cur.x != line->s.x || cur.y != line->s.y)
	{
		draw_thick_point(image, cur, line->thickness, line->color);
		update_error_and_position(&cur, sign, delta, error);
	}
}
