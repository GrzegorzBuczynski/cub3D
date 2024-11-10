/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/10 21:36:28 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_wall(t_game *data)
{
	float	degree;
	int		w_height;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i <= SCREEN_WIDTH)
	{
		// Calculate the angle of the ray
		degree = (-FOV / 2) + ((FOV / SCREEN_WIDTH) * i);
		printf("degree: %f\n", degree);
		// Calculate the distance to the wall
		w_height = 100;
		// Calculate the height of the wall
		// Calculate the color of the wall
		// Draw the wall
		draw_line((t_vector){i, (SCREEN_HEIGHT / 2) - w_height}, (t_vector){i,
			(SCREEN_HEIGHT / 2) + w_height}, &data->display);
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