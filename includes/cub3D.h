/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:44:12 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/09 16:04:17 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/lib_ft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../lib/minilibx/mlx.h"
# include "error_message.h"

// Constants
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define FOV 66.0 // Field of view in degrees
# define TILE_SIZE 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

// Error codes
# define ERR_MAP_LOAD -1
# define ERR_TEXTURE_LOAD -2
# define ERR_MEMORY -3

// check_map
//	// check_borders.c
int		check_borders(char **map);
//	// check_map.c
void	check_map(char **map);

//	// check_player.c
int		check_player(char **map);

// file.c
int		handle_input(char **av, t_game *data);

// utils.c
int		ft_error(int error_code, char *message);

void	print_map(char **map);
void	select_map(t_game *data);
void	init_display(t_display *data);

#endif
