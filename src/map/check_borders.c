/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:47:07 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/15 16:38:59 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	flood_fill(char **map, t_vector pos, t_vector size)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= size.y || pos.x >= size.x)
		return ;
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == '3')
		return ;
	if (map[pos.y][pos.x] == '2' || map[pos.y][pos.x] == '0')
	{
		map[pos.y][pos.x] = '+';
		flood_fill(map, (t_vector){pos.y + 1, pos.x}, size);
		flood_fill(map, (t_vector){pos.y + 1, pos.x + 1}, size);
		flood_fill(map, (t_vector){pos.y + 1, pos.x - 1}, size);
		flood_fill(map, (t_vector){pos.y - 1, pos.x}, size);
		flood_fill(map, (t_vector){pos.y - 1, pos.x + 1}, size);
		flood_fill(map, (t_vector){pos.y - 1, pos.x - 1}, size);
		flood_fill(map, (t_vector){pos.y, pos.x + 1}, size);
		flood_fill(map, (t_vector){pos.y, pos.x - 1}, size);
	}
}

int	alloc_bigger_map(t_game *game, char ***map)
{
	int		i;
	int		j;
	char	**new_map;

	i = 0;
	new_map = gcalloc(sizeof(char *) * (game->map.height + 3), 1);
	if (!new_map)
		close_program(game);
	while (i < game->map.height + 2)
	{
		j = 0;
		new_map[i] = gcalloc(sizeof(char) * (game->map.width + 3), 1);
		if (!new_map[i])
			close_program(game);
		while (j < game->map.width + 3)
		{
			new_map[i][j] = '2';
			j++;
		}
		i++;
	}
	*map = new_map;
	return (0);
}

void	rewrite_map(char **map, char **new_map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] && map[i][j] == '1')
				new_map[i + 1][j + 1] = '1';
			j++;
		}
		i++;
	}
}

int	check_borders(t_game *game)
{
	char		**map;
	t_vector	size;
	t_vector	pos;

	game->map.width = get_maps_max_row_width(game->map.grid);
	game->map.height = get_map_height(game->map.grid);
	init_player(game);
	size = (t_vector){game->map.height + 2, game->map.width + 2};
	pos = (t_vector){game->player.pos.y + 1, game->player.pos.x + 1};
	alloc_bigger_map(game, &map);
	rewrite_map(game->map.grid, map);
	flood_fill(map, pos, size);
	if (map[0][0] == '+')
	{
		printf("Error\nMap is not closed.\n");
		close_program(&game->display);
	}
	return (0);
}
