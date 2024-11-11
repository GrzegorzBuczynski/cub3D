/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/11 13:12:36 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_wall_height(float distance)
{
	int	height;

	height = WALL_FACTOR * (SCREEN_HEIGHT / 2) * distance;
	if (height > SCREEN_HEIGHT / 2)
		height = SCREEN_HEIGHT / 2;
	return (height);
}

int	get_distance(t_game *data, float degree)
{
	int		distance;
	float	radian;
	int		x;
	int		y;

	radian = degree * (M_PI / 180);
	x = data->player.pos.x;
	y = data->player.pos.y;
	distance = 0;
	while (data->map2.grid[y][x] != '1')
	{
		x += cos(radian);
		y += sin(radian);
		distance++;
	}
}

void	print_wall(t_game *data)
{
	float	degree;
	int		w_height;
	float	distance_factor;
	int		i;
	t_line	line;
	int		color;

	i = 0;
	distance_factor = 1;
	color = scale_color(COLOR_CYAN, 0.85);
	while (i <= SCREEN_WIDTH)
	{
		// Calculate the angle of the ray
		degree = (-FOV / 2) + ((FOV / SCREEN_WIDTH) * i);
		printf("degree: %f\n", degree);
		distance_factor = ((float)i / SCREEN_WIDTH);
		printf("distance: %f\n", distance_factor);
		// Calculate the distance to the wall
		// Calculate the height of the wall
		// Calculate the color of the wall
		if (i > SCREEN_WIDTH / 4)
		{
			color = scale_color(COLOR_CYAN, (1 - distance_factor));
			w_height = get_wall_height(distance_factor);
		}
		else
		{
			w_height = 2 * (SCREEN_HEIGHT / 2) * 0.25;
			color = scale_color(COLOR_CYAN, 0.70);
		}
		printf("w_height: %d\n", w_height);
		// Draw the wall
		line = (t_line){(t_vector){i, (SCREEN_HEIGHT / 2) - w_height},
			(t_vector){i, (SCREEN_HEIGHT / 2) + w_height}, color};
		draw_line(&line, &data->display);
		i++;
	}
}

// while (i < SCREEN_WIDTH/lines_per_degree)
// {
// 	j = 0;
// 	while (j < lines_per_degree)
// 	{
// 		draw_line((t_vector){(i * lines_per_degree )+ j, (SCREEN_HEIGHT/2) -50},
// (t_vector){(i * lines_per_degree )+ j, (SCREEN_HEIGHT/2) +50},
// 			&data->display);
// 		j++;
// 	}
// 	// Calculate the angle of the ray
// 	// Calculate the distance to the wall
// 	// Calculate the height of the wall
// 	// Calculate the color of the wall
// 	// Draw the wall
// 	i++;
// }