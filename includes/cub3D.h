/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:44:12 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/11 15:08:25 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/lib_ft/libft.h"
# include "error_message.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// libmlx
# include "../lib/minilibx/mlx.h"
# include "color.h"
# include "key_linux.h"
# include "xfdf.h"

// Math
// # define M_PI 3.142

// Constants
# define SCREEN_WIDTH 1400
# define SCREEN_HEIGHT 600
# define WALL_FACTOR 2
# define FOV 66.0 // Field of view in degrees
# define TILE_SIZE 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define WIDTH 1920
# define MENU_WIDTH 200

# ifndef DEBUG
#  define DEBUG 0
# endif

// Error codes
# define ERR_MAP_LOAD -1
# define ERR_TEXTURE_LOAD -2
# define ERR_MEMORY -3

// check_map
//	// check_borders.c
int		check_borders(char **map);
//	// check_map.c
void	check_map(t_map *map);

//	// check_player.c
int		check_symbols(char **map);

// file.c
int		handle_input(char **av, t_game *data);

// utils.c
int		ft_error(int error_code, char *message);

void	print_map(char **map);
void	select_map(t_game *data);

// display_server
void	init_display(t_game *game);
int		mouse_press(int button, int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);
int		mouse_move(int x, int y, void *param);
void	setup_controls(t_display *data);
// colors.c
int		scale_color(int color, float factor);
int		get_color(t_vector current, t_vector start, t_vector end,
			t_vector delta);
// draw.c --
// void	draw_line(t_vector f, t_vector s, t_display *data);
void	draw_line(t_line *line, t_display *data);
void	print_wall(t_game *data);
int		get_distance(t_game *data, float degree);
// math_utils.c
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_abs(int x);

#endif
