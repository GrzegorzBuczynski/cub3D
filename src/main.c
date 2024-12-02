/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/02 21:34:54 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init(t_game *game)
{
	init_player(game);
	game->player.pos.x = 9;
	game->player.pos.y = 9;
	init_textures_wrapper(game);
	init_display(game);
	mlx_loop_hook(game->display.mlx, draw, game);
	setup_controls(game);
	game->map.width = get_maps_max_row_width(game->map.grid);
	game->map.height = get_map_height(game->map.grid);
	game->params.fps = FPS;
	game->params.limit_fps = 1;
	game->params.speed_ratio = 1;
	game->rc.time_ratio = 1;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (ft_error(1, "Error: Input a map in format *.cub.\n"));
	ft_bzero(&game, sizeof(t_game));
	game.rc.game = &game;
	handle_input(av, &game);
	init(&game);
	mlx_loop(game.display.mlx);
	return (0);
}

