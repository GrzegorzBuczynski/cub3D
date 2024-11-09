

#include "../../cub3D.h"

int	close_window(void *param)
{
	t_display	*window;

	window = (t_display *)param;
	mlx_destroy_image(window->mlx, window->img);
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_display(window->mlx);
	exit(0);
}