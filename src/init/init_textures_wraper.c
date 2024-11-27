/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_wraper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:33:44 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/27 18:54:17 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void init_textures_wrapper(t_game *game)
{
	init_textures(game->array, &game->map);
	// generate_textures(&game->rc.texture, TEX_WIDTH, TEX_HEIGHT);
}

void	generate_textures(int ***table, int texWidth, int texHeight)
{
	int	**textures;

	textures = (int **)malloc(TEX_COUNT * sizeof(int *));
	*table = textures;
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
			textures[3][texWidth * y + x] = COLOR_RED;
			textures[4][texWidth * y + x] = COLOR_TURQUOISE;
			textures[5][texWidth * y + x] = COLOR_MAGENTA;
			textures[6][texWidth * y + x] = COLOR_YELLOW;
			textures[7][texWidth * y + x] = COLOR_BLUE;
		}
	}
}


