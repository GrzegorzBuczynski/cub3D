/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:36:00 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/29 22:41:46 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(int start_time, double expected_time)
{
	int	delta;

	delta = get_time() - start_time;
	while (delta < expected_time && delta > 1000)
	{
		usleep(1000);
		delta = get_time() - start_time;
	}
	while ((get_time() - start_time) < expected_time + 50)
		usleep(50);
}
