/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:36:00 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/01 18:19:39 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

unsigned int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(unsigned int start_time, double expected_time)
{
	int	delta;

	delta = get_time() - start_time;
	while (delta < expected_time && delta > 0)
	{
		usleep(1000);
		delta = get_time() - start_time;
	}
}
