/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:10:52 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/15 16:48:28 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	validate_file_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension == NULL || ft_strncmp(extension, ".cub", 4) != 0)
	{
		ft_error(1, "Error\nInvalid file extension.\n");
		close_program(NULL);
	}
}

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
	validate_file_extension(av[1]);
	read_file(av, &game->array);
	select_map(game);
	if (check_map(&game->map, game))
		close_program(&game->display);
	return (0);
}
