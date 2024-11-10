/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/10 21:09:27 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_wall(t_game *data)
{
	int lines_per_degree;
	int i = 0;
	int j = 0;

	lines_per_degree = SCREEN_WIDTH / FOV;

	while (i < SCREEN_WIDTH/lines_per_degree)
	{
		j = 0;
		while (j < lines_per_degree)
		{
			draw_line((t_vector){(i * lines_per_degree )+ j, (SCREEN_HEIGHT/2) -50}, (t_vector){(i * lines_per_degree )+ j, (SCREEN_HEIGHT/2) +50},
				&data->display);
			j++;
		}
		// Calculate the angle of the ray
		// Calculate the distance to the wall
		// Calculate the height of the wall
		// Calculate the color of the wall
		// Draw the wall
		i++;
	}
}