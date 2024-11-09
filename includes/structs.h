

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player
{
	int pos_y; // Position of the player
	int			pos_x;
	char dir;       // Direction the player is facing
	t_vector plane; // Camera plane for field of view
}				t_player;

typedef struct s_map
{
	char **grid; // 2D array representing the map layout
	int width;   // Width of the map
	int height;  // Height of the map
}				t_map;

typedef struct s_mouse
{
	char		is_pressed;
	int			x;
	int			y;
	int			previous_x;
	int			previous_y;
}				t_mouse;

typedef struct s_display
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			size_line;
	int			bits_per_pixel;
	int			endian;
	t_mouse		mouse;
}				t_display;

typedef struct s_game
{
	char		**array;
	char		**map;
	char		**map_cpy;
	t_player	player;
	t_display	display;
	t_map		map2;
	void *mlx_ptr; // Pointer to the MLX library instance
	void *win_ptr; // Pointer to the game window
}				t_game;