/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/10 22:14:36 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_wall(t_game *data)
{
	float	degree;
	int		w_height;
	float	distance;
	int		i;
	t_line	line;
	int		color;

	i = 0;
	distance = 1;
	color = scale_color(COLOR_CYAN, 0.85);
	w_height = (SCREEN_HEIGHT / 2) * 0.20;
	while (i <= SCREEN_WIDTH)
	{
		// Calculate the angle of the ray
		degree = (-FOV / 2) + ((FOV / SCREEN_WIDTH) * i);
		printf("degree: %f\n", degree);
		distance = ((float)i / SCREEN_WIDTH);
		printf("distance: %f\n", distance);
		// Calculate the distance to the wall
		// Calculate the height of the wall
		// Calculate the color of the wall
		if (i > SCREEN_WIDTH / 5)
		{
			color = scale_color(COLOR_CYAN, (1 - distance));
			w_height = (SCREEN_HEIGHT / 2) * distance;
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