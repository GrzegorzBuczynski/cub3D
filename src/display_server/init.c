

#include "../../cub3D.h"

void	setup_controls(t_fdf *fdf)
{
	// mlx_hook(fdf->win, KEYPRESS, 1L, key_press, fdf);
	// mlx_hook(fdf->win, DESTROYNOTIFY, (1L << 2), close_fdf, fdf);
	// mlx_hook(fdf->win, BUTTONPRESS, (1L << 2), mouse_press, fdf);
	// mlx_hook(fdf->win, BUTTONRELEASE, (1L << 3), mouse_release, fdf);
	// mlx_hook(fdf->win, MOTIONNOTIFY, (1L << 6), mouse_move, fdf);
}


void	init_display(t_display *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_panic(ERR_data_INIT, 1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "data");
	if (!data->win)
		ft_panic(ERR_data_INIT);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		ft_panic(ERR_data_INIT);
	data->data_addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->size_line), &(data->endian));
	setup_controls(&data->display);

}