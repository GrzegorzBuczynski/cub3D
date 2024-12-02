/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:13:11 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/02 17:14:28 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_texture_pixel(t_image *texture, double tex_x, double tex_y)
{
	int				offset;
	unsigned int	*pixel;
	int				x;
	int				y;

	if (!texture || !texture->pixel_data || tex_x < 0 || tex_y < 0 || tex_x > 1
		|| tex_y > 1)
		return (0);
	x = tex_x * texture->width;
	y = tex_y * texture->height;
	offset = y * texture->line_length + x * (texture->bpp / 8);
	pixel = (unsigned int *)(texture->pixel_data + offset);
	return (*pixel);
}
u