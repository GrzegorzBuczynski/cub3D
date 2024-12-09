
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

void	draw_line(t_line *line, t_image *image)
{
	t_vector	delta;
	t_vector	sign;
	t_vector	cur;
	int			error[2];
	int			i;
	int			j;

	estimate_delta(line->s, line->f, &delta);
	calculate_sign(line->s, line->f, &sign);
	error[0] = delta.x - delta.y;
	cur = line->f;
	while (cur.x != line->s.x || cur.y != line->s.y)
	{
		for (i = -line->thickness / 2; i <= line->thickness / 2; i++)
		{
			for (j = -line->thickness / 2; j <= line->thickness / 2; j++)
			{
				put_pixel(image, cur.x + i, cur.y + j, line->color);
			}
		}
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
