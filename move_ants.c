/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:11:05 by okuchko           #+#    #+#             */
/*   Updated: 2019/05/13 14:11:07 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_move_ants(t_graph *b)
{
	int		i;
	int		moves;

	moves = -1;
	b->ants_start = b->ants;
	while (b->ants_end < b->ants)
	{
		moves++;
		i = -1;
		while (b->ways[++i])
			ft_move_ants_in_way(b, i);
		i = -1;
		while (b->ants_start > 0 && b->ways[++i])
		{
			if (b->ants_start > b->ways[i]->expr)
			{
				b->ants_start--;
				b->ways[i]->room[1]->ant = b->ants - b->ants_start;
			}
		}
		if (b->ants_end < b->ants)
			ft_show_move(b);
	}
	ft_printf("Moves = %d\n", moves);
	return (moves);
}

int		ft_move_ants_in_way(t_graph *b, int i)
{
	int		j;

	j = b->ways[i]->length;
	if (b->ways[i]->room[j]->ant)
		b->ants_end++;
	while (j > 0)
	{
		b->ways[i]->room[j]->ant = b->ways[i]->room[j - 1]->ant;
		j--;
	}
	return (1);
}
