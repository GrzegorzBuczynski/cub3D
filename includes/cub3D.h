/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:44:12 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/09 16:55:35 by ssuchane         ###   ########.fr       */
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
# include "key_events.h"
# include <sys/time.h>

// Math
// # define M_PI 3.142

# define true 1
# define false 0

// Minimap
# define MINIMAP_SCALE 15
# define MINIMAP_PADDING_X 20
# define MINIMAP_PADDING_Y 20
# define PLAYER_MINIMAP_VISION_RANGE 15
# define FLOOR_COLOR COLOR_BROWN
# define WALL_COLOR COLOR_AQUA
# define PLAYER_COLOR COLOR_GOLD
# define MINIMAP_TILE_SIZE 10 // Size of each tile on the minimap in pixels
# define MINIMAP_RADIUS 5
// Range of the minimap (5 tiles in each direction)

// Constants
# define SCREEN_WIDTH 1400
# define SCREEN_HEIGHT 800
# define WALL_FACTOR 2
# define FOV 66.0 // Field of view in degrees
# define INITIAL_ROTATION 0.0
# define NORTH -1
# define TILE_SIZE 64
# define STEP_SIZE 0.1
# define TO_WALL_DISTANCE 0.3
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.05
# define FPS 60

# define HORIZONTAL 0
# define VERTICAL 1

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
void			draw_line(t_line *line, t_image *image);
void			draw_square(t_image *image, t_vector pos, int size, unsigned int color);
void			draw_object(t_game *data, char c);
void			draw_background(t_game *game, t_display *display);

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

unsigned int	get_texture_pixel(t_image *texture, double tex_y, double tex_x);
void			add_character_plane(t_game *game);
t_image			*get_texture(t_game *game, char c, double time);
// minimap.c
void			add_minimap(t_game *game);
void			put_pixel(t_image *image, int x, int y, unsigned int color);
void			put_pixel_with_black(t_image *img, int y, int x, unsigned int color);


// mlx_safe.c mlx wrapper
void			*init_mlx_safe(void);
void			*init_window_safe(void *mlx, int width, int height,
					const char *title);
void			*mlx_xpm_file_to_image_safe(void *mlx, const char *path,
					int *width, int *height);
void			*mlx_get_data_addr_safe(void *image, int *bpp, int *line_length,
					int *endian);

void			set_ray_direction(t_game *game, int x);
void			set_step_and_dist(t_game *game);
int				scan_for_hit(t_game *game, char c);
unsigned int	get_time(void);
void			ft_sleep(unsigned int start_time, double expected_time);

// compass.c
void			render_compass(t_game *game);
void			put_image_to_image(t_display *display, t_image *image, int y,
					int x);
t_image			parse_texture2(char *path);
t_image			cut_image(t_image *image, double factor, int width, int *data);

int				parse_color(char *str);
void			trim_texture(t_image *image);
t_image			parse_texture(char *path);
char			*get_path(const char *str);
void			limit_fps(t_game *game);

#endif
