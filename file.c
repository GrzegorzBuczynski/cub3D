/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/08 18:44:01 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	handle_input(char **av)
{
	char	**array;
	int		fd;

	// sometimes it doesn't find a file to open while debugging
	fd = ft_open(av[1]);
	array = ft_read(fd);

	// -----------------------TO DO-----------------------
	// Export textures from map.cub and inilitalize them
	// into structure (4 textures for NORTH, SOUTH, WEST and EAST)
	// -extract path to specific texture
	// -save it into variable
	// Export floor color based on RGB colors in range [0,255] 0, 255, 255

	// ------------------loop for testing------------------
	// while (array[i])
	// {
	// 	printf("%s", array[i]);
	// 	i++;
	// }
	// ----------------------------------------------------

	check_map(array);
	return (1);
}

