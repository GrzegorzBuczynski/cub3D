/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:43:07 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/12 17:28:34 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	fps_counter(t_game *game, int frame_time)
{
	static int	i = 0;
	static int	arr[20] = {0};
	int			avg;
	int			fps;

	avg = 0;
	fps = 1000 / frame_time;
	arr[i] = fps;
	i = (i + 1) % 20;
	for (int j = 0; j < 20; j++)
		avg += arr[j];
	avg /= 20;
	mlx_string_put(game->display.mlx, game->display.win, 1315, 30, 0xFFFFFF,
		"FPS: ");
	mlx_string_put(game->display.mlx, game->display.win, 1350, 30, 0xFFFFFF,
		ft_itoa(avg));
}

void	set_times(t_game *game)
{
	game->time.new_time = get_time();
	game->time.frame_time = game->time.new_time - game->time.old_time;
	game->time.old_time = game->time.new_time;
	fps_counter(game, (int)game->time.frame_time);
	game->rc.time_ratio = game->time.frame_time / 16.0;
}

void	update_frame_nbr(t_raycaster *rc)
{
	rc->sec_part += 1.0 / FPS;
	if (rc->sec_part > 1)
		rc->sec_part -= 1;
}

int	draw(t_game *game)
{
	t_display	*display;
	void		*mlx_img;
	t_raycaster	*rc;

	game->time.start_time = get_time();
	rc = &game->rc;
	display = &game->display;
	draw_background(game, display);
	draw_object(game, '1');
	draw_object(game, 'B');
	render_compass(game);
	add_minimap(game);
	mlx_put_image_to_window(display->mlx, display->win, display->mlx_img, 0, 0);
	limit_fps(game);
	set_times(game);
	move(game);
	update_frame_nbr(rc);
	return (0);
}
