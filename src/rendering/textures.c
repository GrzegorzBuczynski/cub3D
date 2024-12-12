/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:13:11 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/12 19:19:43 by ssuchane         ###   ########.fr       */
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

unsigned int	get_texture_pixel(t_image *texture, double tex_y, double tex_x)
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
	pixel = (unsigned int *)(texture->pixel_data);
	return (pixel[offset / 4]);
}

t_image	*get_wall_texture_by_side(t_game *game)
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

t_image	*get_texture_by_type(t_game *game, char c, double time)
{
	int	i;
	int	number;
	int	frames_count;

	i = 0;
	frames_count = game->animation[i].frames_count;
	number = (int)((time * game->animation[i].speed) * frames_count)
		% frames_count;
	while (game->animation[i].type != c && game->animation[i].type != '\0')
		i++;
	return (&game->animation[i].frames[number]);
}

t_image	*get_texture(t_game *game, char c, double time)
{
	if (c == '1')
		return (get_wall_texture_by_side(game));
	else
		return (get_texture_by_type(game, c, time));
}
