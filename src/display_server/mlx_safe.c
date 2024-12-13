/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_safe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/13 19:35:18 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	*init_mlx_safe(void)
{
	void	*mlx;

	mlx = register_pointer(mlx_init());
	if (!mlx)
		ft_panic("Error.\nFailed to initialize mlx.\n", 1);
	return (mlx);
}

void	*init_window_safe(void *mlx, int width, int height, const char *title)
{
	void	*win;

	if (!mlx)
		ft_panic("Error.\nMLX instance is NULL.\n", 1);
	win = mlx_new_window(mlx, width, height, (char *)title);
	if (!win)
		ft_panic("Error.\nFailed to initialize window.\n", 1);
	return (win);
}

void	*mlx_xpm_file_to_image_safe(void *mlx, const char *path, int *width,
		int *height)
{
	void	*image;

	if (!mlx || !path)
	{
		ft_putstr_fd("Error.\nInvalid MLX instance or path for XPM file\n", 2);
		return (NULL);
	}
	image = mlx_xpm_file_to_image(mlx, (char *)path, width, height);
	if (!image)
	{
		ft_putstr_fd("Error.\nFailed to load XPM file\n", 2);
		return (NULL);
	}
	return (image);
}

void	*mlx_get_data_addr_safe(void *image, int *bpp, int *line_length,
		int *endian)
{
	void	*pixel_data;

	if (!image || !bpp || !line_length || !endian)
	{
		ft_panic("Error.\nInvalid arguments to mlx_get_data_addr\n", 1);
		return (NULL);
	}
	pixel_data = mlx_get_data_addr(image, bpp, line_length, endian);
	if (!pixel_data)
	{
		ft_panic("Error.\nFailed to get pixel data address\n", 1);
		return (NULL);
	}
	return (pixel_data);
}
