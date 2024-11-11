/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/11 18:13:40 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_distance(t_game *data, float degree)
{
	t_vector	player;
	t_vector	tar;
	float		x;
	float		y;

	player = (t_vector){data->player.tile.x, data->player.tile.y};
	tar = player;
	x = (float)player.x;
	y = (float)player.y;
	while (data->map2.grid[tar.y][tar.x] != '1')
	{
		printf("x: %f y: %f\n", x, y);
		printf("char = %c\n", data->map2.grid[(int)y][(int)x]);
		y = y - cos(degree * (M_PI / 180));
		x = x + sin(degree * (M_PI / 180));
		tar.x = (int)round(x);
		tar.y = (int)round(y);
		printf("tar.x: %d tar.y: %d\n", tar.x, tar.y);
	}
	tar = (t_vector){x, y};
	return (ft_min(tar.x, tar.y));
}

int	main(int ac, char **av)
{
	t_game	data;
	int		i;
	int		distance;
	float	distancey;
	float	distancex;
	float	degree;
	float	x;
	float	y;
	float	grad;

	if (ac != 2)
		return (ft_error(1, "Error: Input a map in format *.cub.\n"));
	handle_input(av, &data);
	distance = 0;
	data.player.pos.x = 50;
	data.player.pos.y = 50;
	data.player.tile.x = 1;
	data.player.tile.y = 2;
	data.map2.width = 25;
	data.map2.height = 14;
	distancey = 0;
	distancex = 0;
	degree = 0;
	x = 0.3;
	y = 0.4;
	distance = get_distance(&data, degree);
	// distancey = (y / (cos(degree * (M_PI / 180)))); //
	// distancex = x / (sin(degree * (M_PI / 180)));
	// printf("distancey: %f\n", distancey);
	// printf("distancex: %f\n", distancex);
	printf("distance: %d\n", distance);
	// init_display(&data);
	// mlx_loop(data.display.mlx);
	return (0);
}

// void	print_cos(float degree)
// {
// 	float	radian;

// 	radian = degree * (M_PI / 180);
// 	printf("%f, ", cos(radian));
// }

// grad = 0;
// while (grad < 360)
// {
// 	print_cos(grad);
// 	grad += 0.05;
// }

// int	get_distance(t_game *data, float degree)
// {
// 	int		distance;
// 	float	radian;
// 	float	x;
// 	float	y;

// 	radian = degree * (M_PI / 180); // Konwersja stopni na radiany
// 	x = data->player.tile.x;
// 	y = data->player.tile.y;
// 	distance = -1;
// 	printf("x: %f\n", x);
// 	printf("y: %f\n", y);
// 	printf("\n");
// 	while (data->map2.grid[(int)y][(int)x] != '1')
// 		// Sprawdzanie czy współrzędne nie trafiają na '1'
// 	{
// 		y -= cos(radian); // Przemieszczanie się w kierunku kąta
// 		x += sin(radian);
// 		printf("x: %f\n", x);
// 		printf("y: %f\n", y);
// 		printf("\n");
// 		distance++;
// 	}
// 	return (distance); // Zwrócenie odległości
// }
///

//
//

// float radian = degree * (M_PI / 180); // Convert degrees to radians
// x = (float)data->player.tile.x;
// y = (float)data->player.tile.y;
// float step_size = 0.1; // Step size for finer increments
// rx = data->player.tile.x;
// ;
// ry = data->player.tile.y;
// print_map(data->map2.grid);
// printf("\n");
// printf("Initial x: %f, y: %f\n", x, y);
// printf("char = %c\n", data->map2.grid[(int)y][(int)x]);
// while (data->map2.grid[(int)ry][(int)rx] != '1')
// {
// 	printf("cos(radian = %f\n", cos(radian));
// 	y += -cos(radian); // Move in the direction of the angle
// 	x += sin(radian);
// 	printf("Updated x: %f, y: %f\n", x, y);
// 	rx = (int)(x + 0.5);
// 	ry = (int)(y + 0.5);
// 	printf("rx = %d ry = %d\n", rx, ry);
// 	// distance++;
// 	printf("char = %c\n", data->map2.grid[ry][rx]);
// }

// rx = data->player.tile.x - x;
// ry = data->player.tile.y - y;


// int	get_distance(t_game *data, float degree)
// {
// 	t_vector	player;
// 	t_vector	tar;
// 	float		x;
// 	float		y;

// 	player = (t_vector){data->player.tile.x, data->player.tile.y};
// 	tar = player;
// 	x = (float)player.x;
// 	y = (float)player.y;
// 	while (data->map2.grid[tar.y][tar.x] != '1')
// 	{
// 		printf("x: %f y: %f\n", x, y);
// 		printf("char = %c\n", data->map2.grid[(int)y][(int)x]);
// 		y = y - cos(degree * (M_PI / 180));
// 		x = x + sin(degree * (M_PI / 180));
// 		tar.x = (int)round(x);
// 		tar.y = (int)round(y);
// 		printf("tar.x: %d tar.y: %d\n", tar.x, tar.y);
// 	}
// 	tar = (t_vector){x, y};
// 	return (ft_min(tar.x, tar.y));
// }