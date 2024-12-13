/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:38:53 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/13 17:37:32 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_map(t_map *map)
{
	int	status;

	status = 0;
	status += check_player(map->grid);
	status += check_borders(map);
	if (status)
		ft_error(1, "Error\nInvalid map.\n");
}
