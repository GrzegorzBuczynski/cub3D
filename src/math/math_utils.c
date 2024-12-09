/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:45:09 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 18:41:29 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_min_int(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_min_double(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}
