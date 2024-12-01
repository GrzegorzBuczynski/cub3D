/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:36:00 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/01 00:47:43 by ssuchane         ###   ########.fr       */
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
	while (delta < expected_time && delta > 2)
	{
		usleep(1000);
		delta = get_time() - start_time;
	}
	while ((get_time() - start_time) < expected_time)
		usleep(50);
}
