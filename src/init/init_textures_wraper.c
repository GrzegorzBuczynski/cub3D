/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_wraper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:33:44 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 18:42:27 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_animation(char **file, t_animation *animation)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (file[y])
	{
		if (ft_strncmp(file[y], "ANIMATION ", 9) == 0)
		{
			animation->type = file[y][10];
			animation->frames_count = ft_atoi(&file[y][12]);
			animation->speed = ft_atoi(&file[y][14]);
			y++;
			while (file[y] && file[y] != 0 && x < animation->frames_count)
			{
				animation->frames[x] = parse_texture(get_path(file[y]));
				y++;
				x++;
			}
			animation++;
		}
		y++;
	}
}

void	init_textures_wrapper(t_game *game)
{
	init_textures(game->array, &game->map);
	init_animation(game->array, &game->animation[0]);
}
