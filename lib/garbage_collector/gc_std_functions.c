/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_std_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:49:34 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/12 20:44:13 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	*gmalloc(size_t size)
{
	void	*ptr;

	ptr = gc_collector(malloc(size), false, 1);
	if (!ptr)
		gexit(0);
	return (ptr);
}

void	*gcalloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = gc_collector(calloc(nmemb, size), false, 1);
	if (!ptr)
		gexit(0);
	return (ptr);
}

void	gfree(void *ptr)
{
	gc_collector(ptr, true, 1);
}

void	gexit(int status)
{
	gc_collector(NULL, true, 1);
	exit(status);
}

void	*register_pointer(void *ptr)
{
	gc_collector(ptr, false, 1);
	return (ptr);
}
