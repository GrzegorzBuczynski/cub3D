/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:37:43 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/10 17:54:25 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_error(int error_code, char *message)
{
	ft_putstr_fd(message, 2);
	return (error_code);
}




//temporary
void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
	printf("\n");
}

//temporary
void	print_map_nl(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("\n");
	printf("\n");
}
