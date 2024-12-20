/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:36:00 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 18:59:53 by ssuchane         ###   ########.fr       */
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
	int	sleep_time;

	delta = get_time() - start_time;
	sleep_time = expected_time - delta - 1;
	if (sleep_time > 0)
		usleep(sleep_time * 1000);
}
