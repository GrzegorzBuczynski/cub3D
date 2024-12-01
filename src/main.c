/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/01 18:30:06 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init(t_game *game)
{
	init_player(game);
	init_textures_wrapper(game);
	init_display(game);
	mlx_loop_hook(game->display.mlx, draw, game);
	setup_controls(game);
	game->params.fps = 60;
	game->params.limit_fps = 1;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (ft_error(1, "Error: Input a map in format *.cub.\n"));
	ft_bzero(&game, sizeof(t_game));
	game.rc.game = &game;
	handle_input(av, &game);
	init(&game);
	mlx_loop(game.display.mlx);
	return (0);
}

// int	main(void)
// {
// 	void *mlx;
// 	void *img;
// 	int img_width;
// 	int img_height;

// 	mlx = mlx_init(); // Inicjalizacja MiniLibX
// 	img = mlx_xpm_file_to_image(mlx, "pilot.xpm", &img_width,
// 			&img_height);
// 	if (!img)
// 	{
// 		printf("Błąd: nie udało się załadować obrazu XPM\n");
// 		return ;
// 	}

// 	int *pixels;
// 	int bits_per_pixel;
// 	int line_length;
// 	int endian;

// 	pixels = (int *)mlx_get_data_addr(img, &bits_per_pixel, &line_length,
// 			&endian);

// 	for (int y = 0; y < img_height; y++)
// 	{
// 		for (int x = 0; x < img_width; x++)
// 		{
// 			int color = pixels[y * (line_length / 4) + x];
// 				// Odczyt koloru pikseli
// 			printf("Pixel[%d][%d] = %#X\n", y, x, color);
// 		}
// 	}
// }

// int main()
// {
// 	double i = 0;

// 	i = sin(270 * M_PI / 180);

// 	printf("%f\n", i);
// }
