/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:23:36 by ssuchane          #+#    #+#             */
/*   Updated: 2024/12/13 19:45:21 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to an integer.
 *
 * The function takes a string (`nptr`) and converts it into an integer, 
 * interpreting leading whitespace and optional '+' or '-' signs.
 * It stops conversion when a non-numeric character is encountered.
 *
 * @param nptr The string to be converted to an integer.
 * 
 * @return The integer representation of the string. If the string is empty 
 *         or does not start with a valid numeric character, the function 
 *         returns 0.
 * 
 * @note The function handles optional leading whitespaces and signs 
 *       ('+' or '-'). It only processes digits and stops conversion at 
 *       the first non-digit character.
 * 
 * @warning The function does not handle overflow or underflow cases. 
 *          If the input value exceeds the range of `int`, the behavior 
 *          is undefined.
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	isneg;

	i = 0;
	result = 0;
	isneg = 1;
	if (nptr == NULL && nptr[i] == 0)
		return (0);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			isneg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (isneg * result);
}
