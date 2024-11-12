/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:45:09 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/11/11 20:47:52 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_min_int(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
float	ft_min_float(float a, float b)
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

