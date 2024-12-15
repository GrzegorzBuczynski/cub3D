/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/15 16:10:39 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	set_mini_map_params(t_game *game)
{
	t_minimap	*minimap;

	minimap = &game->params.minimap;
	minimap->player_vision_range = PLAYER_MINIMAP_VISION_RANGE;
	minimap->scale = MINIMAP_SCALE;
	minimap->padding = (t_vector){MINIMAP_PADDING_Y, MINIMAP_PADDING_X};
	minimap->size = (t_vector){2 * PLAYER_MINIMAP_VISION_RANGE, 2
		* PLAYER_MINIMAP_VISION_RANGE};
	if (minimap->size.y > game->map.height)
		minimap->size.y = game->map.height;
	if (minimap->size.x > game->map.width)
		minimap->size.x = game->map.width;
	minimap->player_color = PLAYER_COLOR;
	minimap->wall_color = WALL_COLOR;
	minimap->floor_color = FLOOR_COLOR;
}

void	center_mouse_on_start(t_game *game)
{
	int	center_x;
	int	center_y;

	center_x = SCREEN_WIDTH / 2;
	center_y = SCREEN_HEIGHT / 2;
	mlx_mouse_move(game->display.mlx, game->display.win, center_x, center_y);
}

// mlx_mouse_hide(game->display.mlx, game->display.win);

void	init(t_game *game)
{
	init_player(game);
	init_display(game);
	init_textures_wrapper(game);
	center_mouse_on_start(game);
	mlx_loop_hook(game->display.mlx, draw, game);
	setup_controls(game);
	game->map.width = get_maps_max_row_width(game->map.grid);
	game->map.height = get_map_height(game->map.grid);
	game->params.fps = FPS;
	game->params.limit_fps = true;
	game->params.speed_ratio = 1;
	game->rc.time_ratio = 1;
	game->params.scale_color = true;
	set_mini_map_params(game);
	game->time.old_time = get_time();
	game->time.start_time = get_time();
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (ft_error(1, "Error: Input a map in format *.cub.\n"));
	ft_bzero(&game, sizeof(t_game));
	handle_input(av, &game);
	init(&game);
	mlx_loop(game.display.mlx);
	return (0);
}


// https://prod.liveshare.vsengsaas.visualstudio.com/join?70BAFF02F5065AF39EF12F33EA9FAF251226