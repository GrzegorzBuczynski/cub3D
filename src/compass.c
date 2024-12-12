/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/12 18:57:59 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define COMPASS_SIZE 18000

void	render_compass(t_game *game)
{
	int			center_x;
	double		angle;
	t_image		compass;
	int			compass2[COMPASS_SIZE];

	ft_bzero(&compass2, COMPASS_SIZE);
	center_x = SCREEN_WIDTH / 2;
	angle = (game->rc.angle - M_PI / 2) / (2 * M_PI);
	compass = cut_image(&game->map.compass, angle - 0.042, 350, compass2);
	put_image_to_image(&game->display, &compass, 10, (center_x - (compass.width
				/ 2)));
}
