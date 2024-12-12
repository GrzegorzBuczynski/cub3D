/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:28:14 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/12 20:15:50 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static int	free_if_head(void *ptr, t_glist **head)
{
	t_glist	*tmp;

	tmp = *head;
	if (tmp->content == ptr)
	{
		free(tmp->content);
		*head = tmp->next;
		free(tmp);
		return (true);
	}
	return (false);
}

static int	free_if_not_head(void *ptr, t_glist **head)
{
	t_glist	*tmp;
	t_glist	*previous;

	previous = *head;
	tmp = (*head)->next;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			free(tmp->content);
			previous->next = tmp->next;
			free(tmp);
			return (true);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (false);
}

int	gc_find_and_free_node_in_lst(void *ptr, t_glist **head, bool free)
{
	t_glist	*list;
	t_glist	*sublist;

	sublist = NULL;
	if (!ptr || !head || !free)
		return (false);
	list = *head;
	while (list)
	{
		sublist = list->content;
		if (free_if_head(ptr, list->content))
			return (true);
		if (free_if_not_head(ptr, &sublist))
			return (true);
		list = list->next;
	}
	return (false);
}

int	ft_free_lvl_and_content(t_glist *head)
{
	t_glist	*current;
	t_glist	*previous;

	if (!head)
		return (false);
	previous = head->content;
	current = head->content;
	while (current)
	{
		current = current->next;
		free(previous->content);
		free(previous);
		previous = current;
	}
	free(head);
	return (true);
}

void	remove_level_from_root_glist(t_glist **memory, t_glist *previous,
		t_glist *current)
{
	if (previous)
	{
		previous->next = current->next;
		current->next = NULL;
	}
	else
	{
		*memory = current->next;
	}
}
