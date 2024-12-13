/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:38:53 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/13 20:06:45 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_map(t_map *map)
{
	int	status;

	status = 0;
	status += check_player(map->grid);
	if (status)
		return (status);
	status += check_borders(map);
	if (status)
		return (status);
	return(0);
}
