

typedef struct s_vector
{
	int x;
	int y;
} t_vector;

typedef struct s_line
{
	t_vector s;
	t_vector f;
	int color;
} t_line;

typedef struct s_player
{
	float x;
	float y;
	t_vector pos;	// Position of the player
	t_vector tile;	// Tail of the player
	t_vector dir;	// Direction the player is facing
	t_vector plane; // Camera plane for field of view
} t_player;

typedef struct s_map
{
	char **grid; // 2D array representing the map layout
	int width;	 // Width of the map
	int height;	 // Height of the map
} t_map;

typedef struct s_mouse
{
	char is_pressed;
	int x;
	int y;
	int previous_x;
	int previous_y;
} t_mouse;

typedef struct s_camera
{
	// t_projection		projection;
	int zoom;
	double alpha;
	double beta;
	double gamma;
	float z_divisor;
	int x_offset;
	int y_offset;
} t_camera;

typedef struct s_display
{
	void *mlx;
	void *win;
	void *img;
	char *data_addr;
	int size_line;
	int bits_per_pixel;
	int endian;
	t_mouse mouse;
} t_display;

typedef struct s_xpm
{
	void *wall_north;
	void *wall_south;
	void *wall_west;
	void *wall_east;
	int floor;
	int ceiling;
} t_xpm;

typedef struct s_game
{
	char **array;
	char **map;
	char **map_cpy;
	t_player player;
	t_display display;
	t_map map2;
	t_xpm xpm;
	void *mlx_ptr; // Pointer to the MLX library instance
	void *win_ptr; // Pointer to the game window
} t_game;
