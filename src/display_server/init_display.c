/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:19:02 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/03 19:59:04 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_display(t_game *game)
{
	t_display	*display;

	display = &game->display;
	display->game = game;
	display->mlx = mlx_init();
	if (!display->mlx)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->win = mlx_new_window(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"display");
	if (!display->win)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->mlx_img = mlx_new_image(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display->mlx_img)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->img.pixel_data = mlx_get_data_addr(display->mlx_img,
			&(display->img.bpp), &(display->img.line_length),
			&(display->img.endian));
	display->img.width = SCREEN_WIDTH;
	display->img.height = SCREEN_HEIGHT;
}
