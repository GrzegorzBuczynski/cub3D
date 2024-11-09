/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:09:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/09 23:50:01 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	convert_space_to_wall(char **map)
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

static int	find_first_map_row(char **array)
{
	int	x;
	int	y;

	y = 0;
	while (array[y])
	{
		x = -1;
		while (x++, array[y][x])
			if (array[y][x] == '1' && only_whitespace_before(array[y], x))
				return (y);
		y++;
	}
	return (y);
}

int	get_number_of_rows(char **map)
{
	int	rows;

	rows = 0;
	while (*map)
	{
		if (**map == '1' || **map == ' ')
		{
			rows++;
		}
		map++;
	}
	return (rows);
}

// Function to create a 2D copy of the map, excluding '\n' characters
char	**create_map_copy(char **map)
{
	char	**map_cpy;
	int		rows;
	int		i;
	int		j;

	i = 0;
	rows = get_number_of_rows(map);
	map_cpy = malloc(sizeof(char *) * rows);
	while (map[i])
	{
		j = 0;
		map_cpy[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		while (map[i][j])
		{
			map_cpy[i][j] = map[i][j];
			j++;
		}
		map_cpy[i][j] = '\0';
		i++;
	}
	return (map_cpy);
}

char	**memory(void)
{
	char	**array;

	array = calloc(sizeof(char **), 15);
	if (!array)
		return (0);
	array[0] = ft_strdup("        1111111111111111111111111\n");
	array[1] = ft_strdup("        1000000000110000000000001\n");
	array[2] = ft_strdup("        1011000001110000000000001\n");
	array[3] = ft_strdup("        1001000000000000000000001\n");
	array[4] = ft_strdup("111111111011000001110000000000001\n");
	array[5] = ft_strdup("1000000000110000011101111111111111111111\n");
	array[6] = ft_strdup("1111011111111101110000001000100000000001\n");
	array[7] = ft_strdup("1111011111111101110101001000111111111111\n");
	array[8] = ft_strdup("11000000110101011100000010001\n");
	array[9] = ft_strdup("1000000000000000110000001N0011\n");
	array[10] = ft_strdup("10000000000000001101010010001\n");
	array[11] = ft_strdup("110000011101010111110111100111\n");
	array[12] = ft_strdup("11110111111101011101111010001\n");
	array[13] = ft_strdup("11111111111111111111111111111\n");
	return (array);
}

void	select_map(t_game *data)
{
	// int	y;
	// y = find_first_map_row(data->array);
	// data->map = data->array + y;
	data->map = memory();
	if (DEBUG)
		print_map(data->map);
	convert_space_to_wall(data->map);
	if (DEBUG)
		print_map(data->map);
	// get_player_position(data->map);
	data->map_cpy = create_map_copy(data->map);
	print_map(data->map_cpy);
}
