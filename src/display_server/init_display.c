

#include "../../includes/cub3D.h"

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



void	init_display(t_game *game)
{
	t_display	*display;

	display = &game->display;
	display->game = game;
	display->mlx = mlx_init();
	if (!display->mlx)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->win = mlx_new_window(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "display");
	if (!display->win)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->img = mlx_new_image(display->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display->img)
		ft_panic(ERR_DISPLAY_INIT, 1);
	display->data_addr = mlx_get_data_addr(display->img, &(display->bits_per_pixel),	&(display->size_line), &(display->endian));
	setup_controls(display);
	// draw_background(display);

}