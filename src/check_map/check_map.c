/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:38:53 by ssuchane          #+#    #+#             */
/*   Updated: 2024/11/10 18:06:34 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_map(char **map)
{
	int	status;

	status = 0;
	status += check_player(map);
	status += check_borders(map);
	if (status)
	{
		// free all
		// exit
	}
}
