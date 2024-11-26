/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:09:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/26 18:21:14 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static char	*get_path(const char *str)
{
	char	*end;

	while (*str == ' ' || *str == '\t')
		str++;
	end = (char *)(str + ft_strlen(str) - 1);
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = '\0';
	return (ft_strdup(str));
}

t_image	parse_texture(char *path)
{
	t_image	result;
	void		*image;
	void		*mlx;

	mlx = init_mlx_safe();
	image = NULL;
	image = mlx_xpm_file_to_image_safe(mlx, get_path(path), &result.width,
			&result.height);
	result.pixel_data = (char *)mlx_get_data_addr_safe(image, &result.bpp,
			&result.line_length, &result.endian);
	result.pixel_data = ft_strdup(result.pixel_data);
	mlx_destroy_image(mlx, image);
	mlx_destroy_display(mlx);
	return (result);
}

void	init_textures(char **file, t_map *map)
{
	int	y;

	y = 0;
	while (file[y])
	{
		if (ft_strncmp(file[y], "NO ", 3) == 0)
			map->no = parse_texture(&file[y][3]);
		else if (ft_strncmp(file[y], "SO ", 3) == 0)
			map->so = parse_texture(&file[y][3]);
		else if (ft_strncmp(file[y], "WE ", 3) == 0)
			map->we = parse_texture(&file[y][3]);
		else if (ft_strncmp(file[y], "EA ", 3) == 0)
			map->ea = parse_texture(&file[y][3]);
		else if (ft_strncmp(file[y], "F ", 2) == 0)
			map->floor = parse_color(get_path(&file[y][2]));
		else if (ft_strncmp(file[y], "C ", 2) == 0)
			map->ceiling = parse_color(get_path(&file[y][2]));
		y++;
	}
}
