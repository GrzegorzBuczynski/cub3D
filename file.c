/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/07 20:19:11 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_point
{
	int x;
	int y;
} t_point;

int	only_whitespace_before(char *array, int x)
{
	while (x >= 0)
	{
		if (x == 0)
			return (1);
		x--;
		if (array[x] != ' ')
			return (0);
		if (array[x] == ' ')
			continue ;
	}
	return (1);
}


// void	ft_verify(char *array)
// {
// 	t_point	start;

// 	find_map_start(array, &start);

// }

char	**ft_read_file(int fd)
{
	char	**array;
	char	*line;

	array = NULL;
	line = get_next_line(fd);
	while (1)
	{
		if (line == NULL)
		{
			perror("Map is missing.\n");
			break ;
		}
		array = ft_append_argv(array, line);
		line = get_next_line(fd);
	}
	return (array);
}

static void	convert_space_to_wall(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (i++, map[i])
	{
		j = -1;
		while (j++, map[i][j])
			if (map[i][j] == ' ')
				map[i][j] = '1';
	}
}

int	find_first_row_of_map(char **array)
{
	int	x;
	int	y;

	y = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (array[y][x] == '1' && only_whitespace_before(array[y], x))
				return (y);
			x++;
		}
		y++;
	}
	return (y);
}

int	ft_open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

int	handle_input(char **av)
{
	char	**array;
	int		fd;
	int		i;

	fd = ft_open_file(av[1]);
	array = ft_read_file(fd);
	i = find_first_row_of_map(array);
	convert_space_to_wall(&array[i]);
	// loop for testing
	while (array[i])
	{
		printf("%s", array[i]);
		i++;
	}
	// ft_verify(array);
	// ft_initialize();
	return (1);
}

