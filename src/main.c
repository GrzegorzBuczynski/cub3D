/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/12 22:38:52 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

float	set_x(float degree, float x)
{
	if (degree > 0 && degree < 180)
		return (1 - x);
	else if (degree > 180 && degree < 360)
		return (x);
	else
		return (9999);
}

float	set_y(float degree, float y)
{
	if (degree > 90 && degree < 270)
		return (1 - y);
	else if (degree < 90 || degree > 270)
		return (y);
	else
		return (9999);
}

float	getrx(float x, float degree)
{
	if (degree == 0 || degree == 180)
		return (9999);
	return (fabs(x / sin(degree * (M_PI / 180))));
}

float	getry(float y, float degree)
{
	if (degree == 90 || degree == 270)
		return (9999);
	return (fabs(y / cos(degree * (M_PI / 180))));
}

float	get_distance(t_game *data, float degree)
{
	float		rx;
	float		ry;
	float		x;
	float		y;
	t_vector	cord;

	cord = (t_vector){data->player.tile.x, data->player.tile.y};
	x = set_x(degree, data->player.x);
	y = set_y(degree, data->player.y);
	while (data->map2.grid[cord.y][cord.x] != '1')
	{
		rx = getrx(x, degree);
		ry = getry(y, degree);
		if (rx < ry)
		{
			if (degree > 0 && degree < 180)
			{
				x++;
				cord.x++;
			}
			else
			{
				x--;
				cord.x--;
			}
		}
		else
		{
			if ((degree >= 0 && degree < 90)||(degree > 270 && degree <= 360))
			{
				y++;
				cord.y--;
			}
			else
			{
				y++;
				cord.y--;
			}
		}
	}
	rx = getrx(x, degree);
	ry = getry(y, degree);
	return (ft_min_float(rx, ry));
}

int	main(int ac, char **av)
{
	t_game	data;
	int		i;
	float	distance;
	float	distancey;
	float	distancex;
	float	degree;
	float	x;
	float	y;

	degree = 0;
	if (ac != 2)
		return (ft_error(1, "Error: Input a map in format *.cub.\n"));
	handle_input(av, &data);
	distance = 0;
	data.player.tile.x = 1;
	data.player.tile.y = 5;
	data.map2.width = 25;
	data.map2.height = 14;
	distancey = 0;
	distancex = 0;
	data.player.x = 0.3;
	data.player.y = 0.4;
	// distance = get_distance(&data, degree);
	// data.player.pos.x = 50;
	// data.player.pos.y = 50;
	// distancey = (y / (cos(degree * (M_PI / 180)))); //
	// distancex = x / (sin(degree * (M_PI / 180)));
	// printf("distancey: %f\n", distancey);
	// printf("distancex: %f\n", distancex);
	// printf("distance: %f\n", distance);
	init_display(&data);
	mlx_loop(data.display.mlx);
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

/*
We initialize the set up for the rays
- camera_x -> Where is the camera (-1 = left, 0 = center, 1 = right)
- dir_x/y = direction of the ray
- map_x/y = current square of the ray
- deltadist_x/y = distance to go to the next x or y.
*/

// static void	init_raycasting_info(int x, t_ray *ray, t_player *player)
// {
// 	init_ray(ray);
// 	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
// 	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
// 	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
// 	ray->map_x = (int)player->pos_x;
// 	ray->map_y = (int)player->pos_y;
// 	ray->deltadist_x = fabs(1 / ray->dir_x);
// 	ray->deltadist_y = fabs(1 / ray->dir_y);
// }

// /*
// - We are doing the initial set up for the dda
// - dda algorithm will jump one square in each loop eiter in a x or y direction
// - ray->sidedist_x or y = distance from the ray start position to the
// 	next x or y position
// - if x or y < 0 go the next x or y to the left
// - if x or y > 0 go the next x or y to the right
// */

// static void	set_dda(t_ray *ray, t_player *player)
// {
// 	if (ray->dir_x < 0)
// 	{
// 		ray->step_x = -1;
// 		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
// 	}
// 	else
// 	{
// 		ray->step_x = 1;
// 		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
// 	}
// 	if (ray->dir_y < 0)
// 	{
// 		ray->step_y = -1;
// 		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
// 	}
// 	else
// 	{
// 		ray->step_y = 1;
// 		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
// 	}
// }

// /*
// - We implement the DDA algorithm -> the loop will increment 1 square
// -   until we hit a wall
// - If the sidedistx < sidedisty, x is the closest point from the ray
// */

// static void	perform_dda(t_data *data, t_ray *ray)
// {
// 	int	hit;

// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		if (ray->sidedist_x < ray->sidedist_y)
// 		{
// 			ray->sidedist_x += ray->deltadist_x;
// 			ray->map_x += ray->step_x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->sidedist_y += ray->deltadist_y;
// 			ray->map_y += ray->step_y;
// 			ray->side = 1;
// 		}
// 		if (ray->map_y < 0.25
// 			|| ray->map_x < 0.25
// 			|| ray->map_y > data->mapinfo.height - 0.25
// 			|| ray->map_x > data->mapinfo.width - 1.25)
// 			break ;
// 		else if (data->map[ray->map_y][ray->map_x] > '0')
// 			hit = 1;
// 	}
// }

// static void	calculate_line_height(t_ray *ray, t_data *data,
// t_player *player)
// {
// 	if (ray->side == 0)
// 		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
// 	else
// 		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
// 	ray->line_height = (int)(data->win_height / ray->wall_dist);
// 	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
// 	if (ray->draw_start < 0)
// 		ray->draw_start = 0;
// 	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
// 	if (ray->draw_end >= data->win_height)
// 		ray->draw_end = data->win_height - 1;
// 	if (ray->side == 0)
// 		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
// 	else
// 		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
// 	ray->wall_x -= floor(ray->wall_x);
// }

// int	raycasting(t_player *player, t_data *data)
// {
// 	t_ray	ray;
// 	int		x;

// 	x = 0;
// 	ray = data->ray;
// 	while (x < data->win_width)
// 	{
// 		init_raycasting_info(x, &ray, player);
// 		set_dda(&ray, player);
// 		perform_dda(data, &ray);
// 		calculate_line_height(&ray, data, player);
// 		update_texture_pixels(data, &data->texinfo, &ray, x);
// 		x++;
// 	}
// 	return (SUCCESS);
// }