/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:13:11 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/03 19:38:31 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	trim_texture(t_image *image)
{
	double	ratio;

	ratio = (double)image->width / (double)image->height;
	if (!image || !image->pixel_data)
		return ;
	ratio = (double)image->width / (double)image->height;
	if (ratio > 1.25)
		image->width = image->height * 1.25;
	else if (ratio < 0.75)
		image->height = image->width * 0.75;
}

int	get_texture_pixel(t_image *texture, double tex_y, double tex_x)
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

t_image	*get_texture(t_game *game)
{
	if (game->rc.side == 0)
	{
		if (game->rc.raydir.y > 0)
			return (&game->map.so);
		else
			return (&game->map.no);
	}
	else
	{
		if (game->rc.raydir.x > 0)
			return (&game->map.ea);
		else
			return (&game->map.we);
	}
}