/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/10 20:54:10 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**ft_read(int fd)
{
	char	**array;
	char	*line;

	array = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		perror("File read from is empty.\n");
	while (1)
	{
		if (line == NULL)
			break ;
		array = ft_append_argv(array, line);
		line = get_next_line(fd);
	}
	return (array);
}

int	ft_open(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open a file.\n");
		exit(1);
	}
	return (fd);
}

void	read_file(char **av, char ***array)
{
	int	fd;

	fd = ft_open(av[1]);
	*array = ft_read(fd);
	close(fd);
}

int	parse_color(char *str)
{
	char	*temp;
	int		red;
	int		green;
	int		blue;

	temp = str;
	ft_skip_whitespace(&temp);
	red = ft_atoi(temp);
	temp = ft_strchr(temp, ',');
	temp++;
	green = ft_atoi(temp);
	temp = ft_strchr(temp, ',');
	temp++;
	blue = ft_atoi(temp);
	return ((red << 16) | (green << 8) | blue);
}

void	export_textures(t_game *data)
{
	int	y;

	y = 0;
	while (data->array[y])
	{
		if (ft_strncmp(data->array[y], "NO ", 3) == 0)
			data->xpm.wall_north = ft_strdup(data->array[y] + 3);
		else if (ft_strncmp(data->array[y], "SO ", 3) == 0)
			data->xpm.wall_south = ft_strdup(data->array[y] + 3);
		else if (ft_strncmp(data->array[y], "WE ", 3) == 0)
			data->xpm.wall_west = ft_strdup(data->array[y] + 3);
		else if (ft_strncmp(data->array[y], "EA ", 3) == 0)
			data->xpm.wall_east = ft_strdup(data->array[y] + 3);
		else if (ft_strncmp(data->array[y], "F ", 2) == 0)
			data->xpm.floor = parse_color(data->array[y + 2]);
		else if (ft_strncmp(data->array[y], "C ", 2) == 0)
			data->xpm.ceiling = parse_color(data->array[y + 2]);
		y++;
	}
	//	testing
	printf("%p\n", data->xpm.wall_north);
}

// void	init_textures(t_game *data)
// {
// 	data->xpm.floor = mlx_xpm_file_to_image(data->mlx, data.xpm.floor,
// 			&(data->width), &(data->height));
// 	data->xpm.wall_north = mlx_xpm_file_to_image(data->mlx, data.xpm.wall_north,
// 			&(data->width), &(data->height));
// 	data->xpm.wall_south = mlx_xpm_file_to_image(data->mlx, data.xpm.wall_south,
// 			&(data->width), &(data->height));
// 	data->xpm.wall_west = mlx_xpm_file_to_image(data->mlx, data.xpm.wall_west,
// 			&(data->width), &(data->height));
// 	data->xpm.wall_east = mlx_xpm_file_to_image(data->mlx, data.xpm.wall_east,
// 			&(data->width), &(data->height));
// }

int	handle_input(char **av, t_game *data)
{
	read_file(av, &data->array);
	select_map(data);
	check_map(data->map);
	export_textures(data);
	// sometimes it doesn't find a file to open while debugging
	// -----------------------TO DO-----------------------
	// Export textures from map.cub and inilitalize them
	// into structure (4 textures for NORTH, SOUTH, WEST and EAST)
	// -extract path to specific texture
	// -save it into variable
	// Export floor color based on RGB colors in range [0,255] 0, 255, 255
	// ------------------loop for testing------------------
	// ----------------------------------------------------
	// print_map(data->map);
	return (1);
}
