

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player
{
	t_vector pos;   // Position of the player
	t_vector dir;   // Direction the player is facing
	t_vector plane; // Camera plane for field of view
}				t_player;

typedef struct s_map
{
	char **grid; // 2D array representing the map layout
	int width;   // Width of the map
	int height;  // Height of the map
}				t_map;

typedef struct s_game
{
	char		**array;
	char		**map;
	t_player	player;
	t_map		map2;
	void *mlx_ptr; // Pointer to the MLX library instance
	void *win_ptr; // Pointer to the game window
}				t_game;