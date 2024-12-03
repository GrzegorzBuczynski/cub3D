/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:44:12 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/03 18:06:58 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/lib_ft/libft.h"
# include "error_message.h"
# include "structs.h"
# include <X11/X.h>
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
# include <sys/time.h>

// Math
// # define M_PI 3.142

# define true 1
# define false 0

// Minimap
# define MINIMAP_TILE_SIZE 10 // Size of each tile on the minimap in pixels
# define MINIMAP_RADIUS 5
// Range of the minimap (5 tiles in each direction)

// Constants
# define SCREEN_WIDTH 1400
# define SCREEN_HEIGHT 800
# define WALL_FACTOR 2
# define FOV 66.0 // Field of view in degrees
# define INITIAL_ROTATION 0.0
# define INITIAL_PLANE__SIZE 0.66
# define NORTH -1
# define INITIAL_PLAYERDIR NORTH
# define TILE_SIZE 64
# define STEP_SIZE 0.1
# define TO_WALL_DISTANCE 0.3
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.05
# define FPS 60

# define mapWidth 24
# define mapHeight 24

# define TEX_COUNT 8   // Number of textures
# define TEX_WIDTH 64  // Texture width
# define TEX_HEIGHT 64 // Texture heigh
# define TEXWIDTH 512
# define TEXHEIGHT 512

# ifndef DEBUG
#  define DEBUG 0
# endif

// Error codes
# define ERR_MAP_LOAD -1
# define ERR_TEXTURE_LOAD -2
# define ERR_MEMORY -3

// check_map
//	// check_borders.c
int				check_borders(char **map);
//	// check_map.c
void			check_map(char **map);

//	// check_player.c
int				check_player(char **map);
void			init_player(t_game *game);

//	// map_utils.c
void			get_player_position(char **map, t_vector *p_pos);
int				get_maps_row_width(const char *row);
int				get_maps_max_row_width(char **map);
int				get_map_height(char **map);
void			free_map(char **map);
void			convert_spaces_to_walls(char **map);

// handle_input.c
int				handle_input(char **av, t_game *data);

// utils.c
int				ft_error(int error_code, char *message);

void	print_map(char **map);    // temporary
void	print_map_nl(char **map); // temporary

void			select_map(t_game *data);
void			get_player_position(char **map, t_vector *p_pos);
void			init_display(t_game *data);
int				mouse_press(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
void			setup_controls(t_game *game);

// colors.c
unsigned int	scale_color(unsigned int color, double factor);
int				get_color(t_vector current, t_vector start, t_vector end,
					t_vector delta);
// draw.c --
// void	draw_line(t_vector f, t_vector s, t_display *data);
void			draw_line(t_line *line, t_display *data);
void			print_walls(t_game *data);
double			get_distance(t_game *data, double degree);
void			generate_textures(int ***textures, int texWidth, int texHeight);
// void			draw_background(t_display *data);
void			init_textures(char **file, t_map *map);
void			init_textures_wrapper(t_game *game);

// math_utils.c
int				ft_min_int(int a, int b);
double			ft_min_double(double a, double b);
int				ft_max(int a, int b);
int				ft_abs(int x);
int				draw(t_game *game);

// movment.c
int				move(t_game *game);
void			move_front(t_game *game);
void			move_back(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
void			update_dir_n_plane(t_game *game);

void			my_mlx_pixel_put(t_image *image, int x, int y, int color);
int				get_texture_pixel(t_image *texture, int x, int y);
void			add_character_plane(t_game *game);
t_image			*get_texture_directions(t_game *game);
// minimap.c
void			draw_minimap(t_game *game);
void			put_pixel(t_display *display, int x, int y, int color);

// mlx_safe.c mlx wrapper
void			*init_mlx_safe(void);
void			*init_window_safe(void *mlx, int width, int height,
					const char *title);
void			*mlx_xpm_file_to_image_safe(void *mlx, const char *path,
					int *width, int *height);
void			*mlx_get_data_addr_safe(void *image, int *bpp, int *line_length,
					int *endian);

void			ray_direction_calculate(t_game *game, int x);
void			calculate_step_and_dist(t_game *game);
void			set_ray_steps(t_game *game);
void			calculate_wall_parameters(t_game *game);
void			calculate_texture_coordinates(t_game *game);
unsigned int	get_time(void);
void			ft_sleep(unsigned int start_time, double expected_time);

// compass.c
void			render_compass(t_game *game);
void			put_image_to_image(t_display *display, t_image *image, int y,
					int x);
t_image			parse_texture2(char *path);
t_image			cut_image(t_image *image, double factor, int width);

int				parse_color(char *str);
#endif
