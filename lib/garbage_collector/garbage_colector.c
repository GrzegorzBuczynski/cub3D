/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_colector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:57:46 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 19:58:51 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

int	gc_find_and_free_level(t_glist **memory, bool do_free, int lst_nr)
{
	t_glist	*current;
	t_glist	*previous;
	int		i;

	if (!memory || !do_free)
		return (false);
	current = *memory;
	previous = NULL;
	i = 1;
	while (current)
	{
		if (i == lst_nr)
		{
			remove_level_from_root_glist(memory, previous, current);
			ft_free_lvl_and_content(current);
			return (true);
		}
		previous = current;
		current = current->next;
		i++;
	}
	return (false);
}

int	add_to_list(void *content, t_glist **head, int lst_nr)
{
	t_glist	*tmp;
	int		i;
	t_glist	*new_node;

	i = 1;
	if (!head)
		return (false);
	tmp = *head;
	while (i <= lst_nr)
	{
		if (!tmp)
		{
			new_node = ftg_lstnew(NULL);
			ftg_lstadd_back(head, new_node);
			tmp = *head;
		}
		if (i == lst_nr)
		{
			ftg_lstadd_back((t_glist **)&(tmp->content), ftg_lstnew(content));
			return (true);
		}
		i++;
		tmp = tmp->next;
	}
	return (false);
}

void	*gc_collector(void *content, bool do_free, int lst_nr)
{
	static t_glist	*memory;
	long long		i;

	i = (long long)content;
	if (do_free)
	{
		if (i > 1000)
			gc_find_and_free_node_in_lst(content, &memory, do_free);
		else
			gc_find_and_free_level(&memory, do_free, lst_nr);
		return (NULL);
	}
	else
		add_to_list(content, &memory, lst_nr);
	return (content);
}
