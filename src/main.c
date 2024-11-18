/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:42:46 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/18 21:46:58 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <stdio.h>
#include <stdlib.h>

// Function to generate textures, returning a pointer to the allocated memory
void	generate_textures(int ***textures, int texWidth, int texHeight)
{
	*textures = (int **)malloc(TEX_COUNT * sizeof(int *));
	if (textures == NULL)
	{
		perror("Failed to allocate memory for textures");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < TEX_COUNT; i++)
	{
		textures[i] = (int *)malloc(texWidth * texHeight * sizeof(int));
		if (textures[i] == NULL)
		{
			perror("Failed to allocate memory for texture");
			exit(EXIT_FAILURE);
		}
	}
	for (int x = 0; x < texWidth; x++)
	{
		for (int y = 0; y < texHeight; y++)
		{
			textures[0][texWidth * y + x] = COLOR_WHITE;
			textures[1][texWidth * y + x] = COLOR_GRAY;
			textures[2][texWidth * y + x] = COLOR_BRICK_RED;
			textures[3][texWidth * y + x] = COLOR_GRAY;
			textures[4][texWidth * y + x] = COLOR_GRAY;
			textures[5][texWidth * y + x] = COLOR_GRAY;
			textures[6][texWidth * y + x] = COLOR_GRAY;
			// textures[7][texWidth * y + x] = COLOR_GRAY;
		}
	}
}

void	init_player(t_data *data)
{
	data->playerdir.x = -1;
	data->playerdir.y = 0;
	data->plane.x = 0;
	data->plane.y = 0.66;
	data->time = 0;
	data->oldTime = 0;
	data->playerpos.x = 22.0;
	data->playerpos.y = 11.5;
}

int	main(int ac, char **av)
{
	t_game	data;
	int		i;
	float	distance;

	if (ac != 2)
		return (ft_error(1, "Error: Input a map in format *.cub.\n"));
	// handle_input(av, &data);
	init_player(&data.a);
	generate_textures(&data.a.texture, TEX_WIDTH, TEX_HEIGHT);
	init_display(&data);
	mlx_loop(data.display.mlx);
	return (0);
}
