/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:47:54 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/25 20:38:20 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_vector
{
	int					x;
	int					y;
}						t_vector;

typedef struct s_dvector
{
	double				x;
	double				y;
}						t_dvector;

typedef struct s_raycaster
{
	double				angle;
	int					*buffer;
	int					color;
	double				camera_x;
	t_dvector			delta_dist;
	int					draw_start;
	int					draw_end;
	double				frameTime;
	struct s_game		*game;
	int					hit;
	double				initial_plane;
	double				initial_playerdir;
	t_dvector			lenght_to;
	int					line_height;
	t_vector			map;
	double				oldTime;
	double				perp_wall_dist;
	int					pitch;
	t_dvector			plane;
	t_dvector			playerdir;
	t_dvector			raydir;
	int					side;
	t_dvector			step;
	double				step_size;
	int					tex_x;
	int					texNum;
	double				tex_pos;
	double				texstep;
	int					**texture;
	double				time;
	double				wall_x;
	t_vector			tex;

}						t_raycaster;

typedef struct s_line
{
	t_vector			s;
	t_vector			f;
	int					color;
}						t_line;

typedef struct s_player
{
	char				direction;
	t_dvector			dir;
	t_dvector			pos;
	t_vector			plane;
	double				step_size;
	t_dvector			step_side_side;
	t_dvector			step_top_down;
}						t_player;

typedef struct s_mouse
{
	char				is_pressed;
	int					x;
	int					y;
	int					previous_x;
	int					previous_y;
}						t_mouse;

typedef struct s_camera
{
	// t_projection		projection;
	int					zoom;
	double				alpha;
	double				beta;
	double				gamma;
	double				z_divisor;
	int					x_offset;
	int					y_offset;
}						t_camera;

typedef struct s_display
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					size_line;
	int					bits_per_pixel;
	int					endian;
	t_mouse				mouse;
	t_camera			camera;
	struct s_game		*game;
}						t_display;

typedef struct s_square_params
{
	int					x;
	int					y;
	int					size;
	int					color;
}						t_square_params;

typedef struct s_minimap
{
	int					start_x;
	int					start_y;
	int					cell_size;
	int					pixel_x;
	int					pixel_y;
	int					map_x;
	int					map_y;
	int					color;
	t_display			*display;
}						t_minimap;

typedef struct s_xpm
{
	void				*wall_north;
	void				*wall_south;
	void				*wall_west;
	void				*wall_east;
	int					floor;
	int					ceiling;
}						t_xpm;

typedef struct s_map
{
	// t_dataList			*data;
	char				**map;
	int					start_map;
	int					height;
	int					width;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*floor;
	char				*ceiling;
	unsigned int		color_floor;
	unsigned int		color_ceiling;
}						t_map;

typedef struct s_pressed
{
	int					left;
	int					right;
	int					w;
	int					a;
	int					s;
	int					d;
	int					space;
}						t_pressed;
typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_image;

typedef struct s_game
{
	t_raycaster			rc;
	char				**array;
	t_display			display;
	struct s_map		map;
	t_minimap			minimap;
	void *mlx_ptr; // Pointer to the MLX library instance
	char				**map_cpy;
	double				time;
	double				oldTime;
	double				planeX;
	double				planeY;
	t_player			player;
	struct s_pressed	pressed;
	void *win_ptr; // Pointer to the game window
	t_xpm				xpm;
	t_image				*no_img;
	t_image				*so_img;
	t_image				*we_img;
	t_image				*ea_img;
	t_image				*back;
}						t_game;

