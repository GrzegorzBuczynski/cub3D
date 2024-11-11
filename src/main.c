/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/11 15:54:20 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int get_distance(t_game *data, float degree) {
    int distance = 0;
    float radian = degree * (M_PI / 180);  // Convert degrees to radians
    float x = data->player.tile.x;
    float y = data->player.tile.y;
    float step_size = 0.1;  // Step size for finer increments

    printf("Initial x: %f, y: %f\n", x, y);
    
    while (x >= 0 && x < data->map2.width && y >= 0 && y < data->map2.height && 
           data->map2.grid[(int)y][(int)x] != '1') {
        y -= cos(radian);  // Move in the direction of the angle
        x += sin(radian);
        distance++;
        
        printf("Updated x: %f, y: %f\n", x, y);
    }

    return distance * step_size;  // Adjust distance based on step size
}

// int	get_distance(t_game *data, float degree)
// {
// 	int		distance;
// 	float	radian;
// 	float		x;
// 	float		y;

// 	radian = degree * (M_PI / 180);  // Konwersja stopni na radiany
// 	x = data->player.tile.x;
// 	y = data->player.tile.y;
// 	distance = -1;

// 	printf("x: %f\n", x);
// 	printf("y: %f\n", y);
// 	printf("\n");
// 	while (data->map2.grid[(int)y][(int)x] != '1')  // Sprawdzanie czy współrzędne nie trafiają na '1'
// 	{
// 		y -= cos(radian);  // Przemieszczanie się w kierunku kąta
// 		x += sin(radian);
// 		printf("x: %f\n", x);
// 		printf("y: %f\n", y);
// 		printf("\n");
// 		distance++;
// 	}

// 	return distance;  // Zwrócenie odległości
// }

int	main(int ac, char **av)
{
	t_game	data;
	int		i;


	if (ac != 2)
		return (ft_error(1, "Error: Input a map in format *.cub.\n"));
	handle_input(av, &data);


	int distance = 0;	
	
	data.player.pos.x = 50;
	data.player.pos.y = 50;
	data.player.tile.x = 1;
	data.player.tile.y = 1;
	float distancey = 0;
	float distancex = 0;
	float degree = 180;
	float x = 0.3;
	float y = 0.4;
	distance = get_distance(&data, degree);
	
	// distance = get_distance(&data, degree);
	distancey = (y /(cos(degree * (M_PI / 180))));//
	distancex =  x / (sin(degree * (M_PI / 180))); 
	// printf("distancey: %f\n", distancey);
	// printf("distancex: %f\n", distancex);
	printf("distance: %d\n", distance);
	// init_display(&data);
	// mlx_loop(data.display.mlx);
	return (0);
}
