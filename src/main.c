/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ja <ja@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/16 15:03:06 by ja               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	init_player(t_game *data)
{
	// data->player.tile.x = 1;
	// data->player.tile.y = 5;
	// data->player.x = 0.5;
	// data->player.y = 0.5;
	// data->player.step_x = 0.1;
	// data->player.step_y = 0.1;
	data->playerdirX = -1;
	data->playerdirY = 0;
	data->planeX = 0.0;
	data->planeY = 0.66;
	data->time = 0;
	data->oldTime = 0;
	data->playerposX = 22.0;
	data->playerposY = 11.5;

}



int	main(int ac, char **av)
{
	t_game	data;
	int		i;
	float	distance;

	if (ac != 2)
		return (ft_error(1, "Error: Input a map in format *.cub.\n"));
	handle_input(av, &data);
	data.map2.width = 25;
	data.map2.height = 14;
	init_player(&data);
	init_display(&data);
	mlx_loop(data.display.mlx);
	return (0);
}
