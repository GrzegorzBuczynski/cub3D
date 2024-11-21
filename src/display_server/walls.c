/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/21 18:51:17 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define TEXWIDTH 64
#define TEXHEIGHT 64
#define HORIZONTAL 0
#define VERTICAL 1
#define PITCH 100

extern int	worldMap[mapWidth][mapHeight];

void	set_cameraX(t_data *a)
{
	a->cameraX = 2 * a->x / (double)SCREEN_WIDTH - 1;
}

void	set_initial_map_position(t_data *a)
{
	a->map.x = (int)a->game->player.pos.x;
	a->map.y = (int)a->game->player.pos.y;
}

void	set_rayDir(t_data *a)
{
	a->rayDir.x = a->playerdir.x + a->plane.x * a->cameraX;
	a->rayDir.y = a->playerdir.y + a->plane.y * a->cameraX;
}

void	setdeltaDist(t_data *a)
{
	if (a->rayDir.y == 0)
		a->deltaDist.y = 1e30;
	else
		a->deltaDist.y = sqrt(1 + (a->rayDir.x * a->rayDir.x) / (a->rayDir.y * a->rayDir.y));
	if (a->rayDir.x == 0)
		a->deltaDist.x = 1e30;
	else
		a->deltaDist.x = sqrt(1 + (a->rayDir.y * a->rayDir.y) / (a->rayDir.x * a->rayDir.x));
}

void	calculate_step_and_initial_sideDist(t_data *a)
{
	t_player	*player;
	
	player = &a->game->player;
	if (a->rayDir.x < 0)
	{
		a->step.x = -1;
		a->lenght_to.x = (player->pos.x - a->map.x) * a->deltaDist.x;
	}
	else
	{
		a->step.x = 1;
		a->lenght_to.x = (1.0 + a->map.x - player->pos.x) * a->deltaDist.x;
	}
	if (a->rayDir.y < 0)
	{
		a->step.y = -1;
		a->lenght_to.y = (player->pos.y - a->map.y) * a->deltaDist.y;
	}
	else
	{
		a->step.y = 1;
		a->lenght_to.y = (1.0 + a->map.y - player->pos.y) * a->deltaDist.y;
	}
}

void	search_wall_hit(t_data *a)
{
	a->hit = 0;
	while (a->hit == 0)
	{
		if (a->lenght_to.x < a->lenght_to.y)
		{
			a->lenght_to.x += a->deltaDist.x;
			a->map.x += a->step.x;
			a->side = VERTICAL;
		}
		else
		{
			a->lenght_to.y += a->deltaDist.y;
			a->map.y += a->step.y;
			a->side = HORIZONTAL;
		}
		if (worldMap[a->map.x][a->map.y] > 0)
			a->hit = 1;
	}
}

void	calculate_perpendicular_ray(t_data *a)
{
	if (a->side == HORIZONTAL)
		a->perpWallDist = (a->lenght_to.y - a->deltaDist.y);
	else
		a->perpWallDist = (a->lenght_to.x - a->deltaDist.x);
	a->perpWallDist = a->perpWallDist;
}

void	texturing_calculations(t_data *a)
{
	a->texNum = worldMap[a->map.x][a->map.y] - 1;
}

void	calculate_value_of_wallX(t_data *a)
{
	t_player	*player;
	
	player = &a->game->player;
	if (a->side == HORIZONTAL)
		a->wallX = player->pos.y + a->perpWallDist * a->rayDir.y;
	else
		a->wallX = player->pos.x + a->perpWallDist * a->rayDir.x;
	a->wallX -= floor((a->wallX));
}

void	coordinate_on_the_texture(t_data *a)
{
	a->texX = (int)(a->wallX * (double)TEXWIDTH);
	if (a->side == HORIZONTAL && a->rayDir.x > 0)
		a->texX = TEXWIDTH - a->texX - 1;
	if (a->side == VERTICAL && a->rayDir.y < 0)
		a->texX = TEXWIDTH - a->texX - 1;
}

void	calculate_lowest_and_highest_pixel(t_data *a)
{
	a->drawStart = -a->lineHeight / 2 + SCREEN_HEIGHT / 2 + PITCH;
	if (a->drawStart < 0)
		a->drawStart = 0;
	a->drawEnd = a->lineHeight / 2 + SCREEN_HEIGHT / 2 + PITCH;
	if (a->drawEnd >= SCREEN_HEIGHT)
		a->drawEnd = SCREEN_HEIGHT - 1;
}

void	draw_vertical_line(t_data *a)
{
	int	y;
	int	texY;

	y = a->drawStart;
	a->texstep = 1.0 * TEXHEIGHT / a->lineHeight;
	a->texPos = (a->drawStart - 100 - SCREEN_HEIGHT / 2 + a->lineHeight / 2)
		* a->texstep;
	while (y < a->drawEnd)
	{
		texY = (int)a->texPos & (TEXHEIGHT - 1);
		a->texPos += a->texstep;
		a->color = a->texture[a->texNum][TEXWIDTH * texY + a->texX];
		if (a->side == VERTICAL)
			a->color = (a->color >> 1) & 8355711;
		a->buffer[y*SCREEN_WIDTH + a->x] = a->color;
		y++;
	}
}

void line_height(t_data *a)
{
	if (a->perpWallDist == 0)
		a->lineHeight = SCREEN_HEIGHT;
	else
		a->lineHeight = (int)(SCREEN_HEIGHT / a->perpWallDist);
}

void	calc(t_data *a)
{
	a->x = 0;
	while (a->x < SCREEN_WIDTH)
	{
		set_cameraX(a); // x-coordinate in camera space
		set_initial_map_position(a);
		set_rayDir(a);
		setdeltaDist(a);
		calculate_step_and_initial_sideDist(a);
		search_wall_hit(a);
		calculate_perpendicular_ray(a);
		line_height(a);
		// a->lineHeight = (int)(SCREEN_HEIGHT / a->perpWallDist);
		texturing_calculations(a);
		calculate_value_of_wallX(a);
		coordinate_on_the_texture(a);
		calculate_lowest_and_highest_pixel(a);
		draw_vertical_line(a);
		a->x++;
	}
}

void	clear_buffer(int **buffer)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	set_time(t_data *a)
{
	a->oldTime = a->time;
	// a->time = getTicks();
	a->frameTime = (a->time - a->oldTime) / 1000.0;
	printf("%f \n", 1.0 / a->frameTime);
}

void	print_walls(t_game *data)
{
	calc(&data->a);
	// drawBuffer(data->a.buffer[0]);
	// set_time(&data->a);
	// redraw();
}

// int	get_wall_height(double distance)
// {
// 	int	height;

// 	height = WALL_FACTOR * (SCREEN_HEIGHT / 2) / distance;
// 	if (height > SCREEN_HEIGHT / 2)
// 		height = SCREEN_HEIGHT / 2;
// 	return (height);
// }