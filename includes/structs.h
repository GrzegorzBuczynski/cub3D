/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:47:54 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/03 15:23:44 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_vector
{
	int				y;
	int				x;
}					t_vector;

typedef struct s_dvector
{
	double			x;
	double			y;
}					t_dvector;

typedef struct s_image
{
	void			*mlx_image;
	int				width;
	int				height;
	char			*pixel_data;
	int				bpp;
	int				line_length;
	int				endian;
}					t_image;

typedef struct s_raycaster
{
	double			angle;
	int				*buffer;
	int				color;
	double			camera_x;
	t_dvector		delta_dist;
	int				draw_start;
	int				draw_end;
	struct s_game	*game;
	int				hit;
	double			initial_plane;
	double			initial_playerdir;
	t_dvector		lenght_to;
	int				line_height;
	t_vector		map;
	double			perp_wall_dist;
	int				pitch;
	t_dvector		raydir;
	int				side;
	t_dvector		step;
	double			step_size;
	int				tex_x;
	int				texNum;
	double			tex_pos;
	double			texstep;
	// int					**texture;
	t_image			*texture;
	double			time_ratio;
	double			wall_x;
	t_dvector		tex;

}					t_raycaster;

typedef struct s_line
{
	t_vector		s;
	t_vector		f;
	int				color;
}					t_line;

typedef struct s_player
{
	char			direction;
	double			ini_dir;
	double			ini_plane;
	t_dvector		dir;
	t_dvector		pos;
	t_dvector		plane;
	double			step_size;
	t_dvector		step_side_side;
	t_dvector		step_top_down;
}					t_player;

typedef struct s_mouse
{
	char			is_pressed;
	int				x;
	int				y;
	int				previous_x;
	int				previous_y;
}					t_mouse;

typedef struct s_camera
{
	// t_projection		projection;
	int				zoom;
	double			alpha;
	double			beta;
	double			gamma;
	double			z_divisor;
	int				x_offset;
	int				y_offset;
}					t_camera;

typedef struct s_display
{
	void			*mlx;
	void			*win;
	void			*mlx_img;
	t_image			img;
	t_mouse			mouse;
	t_camera		camera;
	struct s_game	*game;
}					t_display;

typedef struct s_square_params
{
	int				y;
	int				x;
	int				size;
	int				color;
}					t_square_params;

typedef struct s_minimap
{
	t_image			image;
	int				start_y;
	int				start_x;
	int				cell_size;
	int				pixel_y;
	int				pixel_x;
	int				map_x;
	int				map_y;
	int				color;
	t_display		*display;
}					t_minimap;

typedef struct s_xpm
{
	void			*wall_north;
	void			*wall_south;
	void			*wall_west;
	void			*wall_east;
	int				floor;
	int				ceiling;
}					t_xpm;

typedef struct s_map
{
	// t_dataList			*data;
	char			**grid;
	int				start_map;
	int				height;
	int				width;
	t_image			no;
	t_image			so;
	t_image			we;
	t_image			ea;
	unsigned int	floor;
	unsigned int	ceiling;
	t_image			compass;
	t_image			texture;
}					t_map;

typedef struct s_pressed
{
	int				left;
	int				right;
	int				w;
	int				a;
	int				s;
	int				d;
	int				space;
	int 			shift;
}					t_pressed;

typedef struct s_time
{
	unsigned int	old_time;
	unsigned int	new_time;
	unsigned int	frame_time;
	double			move_speed;
	double			rot_speed;
}					t_time;

typedef struct s_params
{
	int				fps;
	int				limit_fps;
	double			speed_ratio;
	int				jump;
	int				scale_color;
}					t_params;

typedef struct s_game
{
	char			**array;
	char			**map_cpy;
	t_display		display;
	t_raycaster		rc;
	t_map			map;
	t_minimap		minimap;
	t_pressed		pressed;
	t_player		player;
	t_time			time;
	t_params		params;
}					t_game;
