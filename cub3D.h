/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:44:12 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/07 17:50:18 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H_
# define _CUB3D_H_

# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

// Constants
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define FOV 66.0         // Field of view in degrees
# define TILE_SIZE 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

// Error codes
# define ERR_MAP_LOAD -1
# define ERR_TEXTURE_LOAD -2
# define ERR_MEMORY -3

typedef struct s_vector
{
    double x;
    double y;
}               t_vector;

typedef struct s_player
{
    t_vector pos;        // Position of the player
    t_vector dir;        // Direction the player is facing
    t_vector plane;      // Camera plane for field of view
}               t_player;

typedef struct s_map
{
    char **grid;         // 2D array representing the map layout
    int width;           // Width of the map
    int height;          // Height of the map
}               t_map;

typedef struct s_game
{
    t_player player;
    t_map map;
    void *mlx_ptr;       // Pointer to the MLX library instance
    void *win_ptr;       // Pointer to the game window
}               t_game;


#endif
