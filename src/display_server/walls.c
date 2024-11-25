/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:31:28 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/25 17:57:50 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define TEXWIDTH 64
#define TEXHEIGHT 64
#define HORIZONTAL 0
#define VERTICAL 1
#define PITCH 0

extern int	worldMap[mapWidth][mapHeight];

void	set_cameraX(t_raycaster *a)
{
	a->cameraX = 2 * a->x / (double)SCREEN_WIDTH - 1;
}

void	set_initial_map_position(t_raycaster *a)
{
	a->map.x = (int)a->game->player.pos.x;
	a->map.y = (int)a->game->player.pos.y;
}

void	set_rayDir(t_raycaster *a)
{
	a->rayDir.x = a->playerdir.x + a->plane.x * a->cameraX;
	a->rayDir.y = a->playerdir.y + a->plane.y * a->cameraX;
}

void	setdeltaDist(t_raycaster *a)
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

void	calculate_step_and_initial_sideDist(t_raycaster *a)
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

void	search_wall_hit(t_raycaster *a)
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

void	calculate_line_height(t_raycaster *a)
{
	if (a->side == HORIZONTAL)
		a->perpWallDist = (a->map.y - a->game->player.pos.y + (1 - a->step.y) / 2) / a->rayDir.y + 0.0001;
	else
		a->perpWallDist = (a->map.x - a->game->player.pos.x + (1 - a->step.x) / 2) / a->rayDir.x + 0.0001;
	a->lineHeight = (int)(SCREEN_HEIGHT / a->perpWallDist);
}




void	texturing_calculations(t_raycaster *a)
{
	a->texNum = worldMap[a->map.x][a->map.y] - 1;
}

void	calculate_value_of_wallX(t_raycaster *a)
{
	t_player	*player;
	
	player = &a->game->player;
	if (a->side == HORIZONTAL)
		a->wallX = player->pos.y + a->perpWallDist * a->rayDir.y;
	else
		a->wallX = player->pos.x + a->perpWallDist * a->rayDir.x;
	a->wallX -= floor((a->wallX));
}

void	coordinate_on_the_texture(t_raycaster *a)
{
	a->texX = (int)(a->wallX * (double)TEXWIDTH);
	if (a->side == HORIZONTAL && a->rayDir.x > 0)
		a->texX = TEXWIDTH - a->texX - 1;
	if (a->side == VERTICAL && a->rayDir.y < 0)
		a->texX = TEXWIDTH - a->texX - 1;
}

void	calculate_lowest_and_highest_pixel(t_raycaster *a)
{
	a->drawStart = -a->lineHeight / 2 + SCREEN_HEIGHT / 2 + PITCH;
	if (a->drawStart < 0)
		a->drawStart = 0;
	a->drawEnd = a->lineHeight / 2 + SCREEN_HEIGHT / 2 + PITCH;
	if (a->drawEnd >= SCREEN_HEIGHT)
		a->drawEnd = SCREEN_HEIGHT - 1;
}

void	draw_vertical_line(t_raycaster *a)
{
	int	y;
	int	texY;

	y = a->drawStart;
	a->texstep = 1.0 * TEXHEIGHT / a->lineHeight;
	a->texPos = (a->drawStart - PITCH - SCREEN_HEIGHT / 2 + a->lineHeight / 2)
		* a->texstep;
	while (y < a->drawEnd)
	{
		texY = (int)a->texPos & (TEXHEIGHT - 1);
		a->texPos += a->texstep;
		a->color = a->texture[a->texNum][TEXWIDTH * texY + a->texX];
		if (a->side == VERTICAL)
			a->color = (a->color >> 1) & 8355711;
		a->buffer[y*SCREEN_WIDTH + a->x] = scale_color(a->color,a->perpWallDist/15);
		y++;
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

void	set_time(t_raycaster *a)
{
	a->oldTime = a->time;
	// a->time = getTicks();
	a->frameTime = (a->time - a->oldTime) / 1000.0;
	printf("%f \n", 1.0 / a->frameTime);
}

void	print_walls(t_game *game)
{
	t_raycaster	*rc;

	rc = &game->rc;
	rc->x = 0;
	while (rc->x < SCREEN_WIDTH)
	{
		set_cameraX(rc); // x-coordinate in camera space
		set_initial_map_position(rc);
		set_rayDir(rc);
		setdeltaDist(rc);
		calculate_step_and_initial_sideDist(rc);
		search_wall_hit(rc);
		calculate_line_height(rc);
		texturing_calculations(rc);
		calculate_value_of_wallX(rc);
		coordinate_on_the_texture(rc);
		calculate_lowest_and_highest_pixel(rc);
		draw_vertical_line(rc);
		rc->x++;
	}
}

// int	get_wall_height(double distance)
// {
// 	int	height;

// 	height = WALL_FACTOR * (SCREEN_HEIGHT / 2) / distance;
// 	if (height > SCREEN_HEIGHT / 2)
// 		height = SCREEN_HEIGHT / 2;
// 	return (height);
// }