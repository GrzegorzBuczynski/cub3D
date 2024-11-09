

#include "../../cub3D.h"

// static void	draw_background(t_game *data)
// {
// 	int	*image;
// 	int	i;

// 	ft_bzero(data->data_addr, SCREEN_WIDTH *SCREEN_HEIGHT * (data->bits_per_pixel / 8));
// 	image = (int *)(data->data_addr);
// 	i = 0;
// 	while (i <SCREEN_HEIGHT *SCREEN_WIDTH)
// 	{
// 		if (i %SCREEN_WIDTH < MENU_WIDTH)
// 			image[i] = MENU_BACKGROUND;
// 		else
// 			image[i] = BACKGROUND;
// 		i++;
// 	}
// }

// void	setup_controls(t_display *data)
// {
// 	mlx_hook(data->win, KEYPRESS, 1L, key_press, data);
// 	mlx_hook(data->win, DESTROYNOTIFY, (1L << 2), close_data, data);
// 	mlx_hook(data->win, BUTTONPRESS, (1L << 2), mouse_press, data);
// 	mlx_hook(data->win, BUTTONRELEASE, (1L << 3), mouse_release, data);
// 	mlx_hook(data->win, MOTIONNOTIFY, (1L << 6), mouse_move, data);
// }


void	init_display(t_display *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_panic(ERR_DISPLAY_INIT, 1);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "data");
	if (!data->win)
		ft_panic(ERR_DISPLAY_INIT, 1);
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->img)
		ft_panic(ERR_DISPLAY_INIT, 1);
	data->data_addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),	&(data->size_line), &(data->endian));
	// setup_controls(data);
	// draw_background(data);

}