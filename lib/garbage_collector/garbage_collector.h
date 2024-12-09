/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:06:18 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/12/09 19:58:13 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_glist
{
	void			*content;
	struct s_glist	*next;
}					t_glist;

int					gc_find_and_free_node_in_lst(void *ptr, t_glist **head,
						bool free);
int					gc_find_and_free_level(t_glist **to_free, bool do_free,
						int lst_nr);
void				*gc_collector(void *content, bool do_free, int lst_nr);
t_glist				*ftg_lstnew(void *content);
void				ftg_lstadd_back(t_glist **lst, t_glist *new);
void				remove_level_from_root_glist(t_glist **memory,
						t_glist *previous, t_glist *current);
int					ft_free_lvl_and_content(t_glist *head);

void				*gmalloc(size_t size);
void				*gcalloc(size_t nmemb, size_t size);
void				gfree(void *ptr);
void				gexit(int status);
void				register_pointer(void *ptr);

#endif
