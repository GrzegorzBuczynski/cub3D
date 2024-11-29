/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:27:13 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/26 18:28:40 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	close_window(void *param)
{
	t_display	*window;

	window = (t_display *)param;
	mlx_destroy_image(window->mlx, window->mlx_img);
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_display(window->mlx);
	exit(0);
}
