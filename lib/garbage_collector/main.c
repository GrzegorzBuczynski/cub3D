/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:16:21 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/12 20:17:01 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

int	main(void)
{
	int	*a;
	int	*b;

	a = (int *)gmalloc(sizeof(int));
	b = (int *)gmalloc(sizeof(int));
	*a = 10;
	printf("a = %d\n", *a);
	gfree(a);
	gexit(0);
}
