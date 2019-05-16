/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:09:53 by okuchko           #+#    #+#             */
/*   Updated: 2019/05/13 14:09:57 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_bfs(t_graph *b)
{
	t_room	*tmp;
	t_link	*t;
	int		i;
	int		j;

	ft_buf_clean(b);
	tmp = b->end;
	b->buf[0] = tmp;
	i = 0;
	j = 1;
	while (tmp && tmp != b->start)
	{
		if ((tmp->on_off == on) && (t = tmp->link))
			while (t)
			{
				if (t->room->parent == NULL && (t->room->on_off == on))
				{
					t->room->parent = tmp;
					b->buf[j++] = t->room;
				}
				t = t->next;
			}
		tmp = b->buf[++i];
	}
	return (tmp == b->start ? i : 0);
}

void	ft_buf_clean(t_graph *b)
{
	int	i;

	if (b->n_rooms > 0)
	{
		i = 0;
		while (i < b->n_rooms + 1)
			b->buf[i++] = NULL;
	}
}
