/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/01 00:29:19 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_compass(t_game *game)
{
	t_display	*display;
	int			center_x;
	double		angle;
	t_image		compass;
;

	display = &game->display;
	center_x = SCREEN_WIDTH / 2;
	int center_y = 50; // Top of the screen
	angle = (game->rc.angle - M_PI / 2) / (2 * M_PI);
	compass = cut_image(&game->map.compass, angle - 0.011 , 350);
	put_image_to_image(&game->display, &compass, 10, (center_x - (compass.width / 2)));
}

// Render compass base
// mlx_put_image_to_window(display->mlx, display->win,
	// game->map.compass_base.mlx_image,
// center_x - (game->map.compass_needle.width / 2), center_y
	// - (game->map.compass_needle.height / 2));
// center_x - (game->map.compass_base.width / 2), center_y
	// - (game->map.compass_base.height / 2));
// Render compass needle with rotation
// mlx_put_image_to_window(display->mlx, display->win,
	// game->map.compass_needle.mlx_image,