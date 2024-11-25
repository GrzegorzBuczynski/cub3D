/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:26:39 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/25 20:34:19 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3D.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	*pixel;

	if (!texture || !texture->addr || tex_x < 0 || tex_y < 0
		|| tex_x >= TEXWIDTH || tex_y >= TEXHEIGHT)
		return (0);
	offset = tex_y * (texture->line_length / (texture->bits_per_pixel / 8))
		+ tex_x;
	pixel = (unsigned int *)(texture->addr + offset * (texture->bits_per_pixel
				/ 8));
	return (*pixel);
}

void	add_character_plane(t_game *game)
{
	char	plane;

	plane = game->player.direction;
	if (plane == 'S')
	{
		game->player.dir.x = 1;
		game->player.plane.y = -0.66;
	}
	else if (plane == 'N')
	{
		game->player.dir.x = -1;
		game->player.plane.y = 0.66;
	}
	else if (plane == 'E')
	{
		game->player.dir.y = 1;
		game->player.plane.x = 0.66;
	}
	else if (plane == 'W')
	{
		game->player.dir.y = -1;
		game->player.plane.x = -0.66;
	}
}

t_image	*get_texture_directions(t_game *game)
{
	if (game->rc.side == 0)
	{
		if (game->rc.raydir.x > 0)
			return (game->so_img);
		else
			return (game->no_img);
	}
	else
	{
		if (game->rc.raydir.y > 0)
			return (game->ea_img);
		else
			return (game->we_img);
	}
}