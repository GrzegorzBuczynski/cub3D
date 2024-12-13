/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/13 17:38:20 by ssuchane         ###   ########.fr       */
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
		perror("Error\nFile read from is empty.\n");
	while (1)
	{
		if (line == NULL)
			break ;
		register_pointer(line);
		array = register_pointer(ft_append_argv(array, line));
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
		perror("Error\nFailed to open a file.\n");
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

int	handle_input(char **av, t_game *game)
{
	read_file(av, &game->array);
	select_map(game);
	check_map(&game->map);
	return (1);
}
