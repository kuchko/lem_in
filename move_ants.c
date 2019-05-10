#include "lem_in.h"

int		ft_move_ants(t_graph *b)
{
	int i;
	int moves;

	moves = -1;
	b->ants_start = b->ants;

	// ft_printf("antd %d - %d", b->start->ant, b->ants_end);
	while (b->ants_end < b->ants)
	{
		moves++;
		i = -1;
		while(b->ways[++i])
			ft_move_ants_in_way(b, i);
		i = -1;
		while (b->ants_start > 0 && b->ways[++i])
		{
			// ft_printf("ant start %d", b->start->ant);

			if (b->ants_start > b->ways[i]->expr)
			{
				b->ants_start--;
				b->ways[i]->room[1]->ant = b->ants - b->ants_start;
			}
		}
		ft_show_move(b);
	}
	ft_printf("moves = %d\n", moves);
	return (moves);
}

int		ft_move_ants_in_way(t_graph *b, int i)
{
	int		j;

	j = b->ways[i]->length;
	if (b->ways[i]->room[j]->ant)
	{
		// b->ways[i]->room[j]->ant = 0;
		b->ants_end++;
	}
	while(j > 0)
	{
		// if (b->ways[i]->room[j]->ant)
			b->ways[i]->room[j]->ant = b->ways[i]->room[j - 1]->ant;
		j--;
	}
	return (1);
}

int		ft_show_move(t_graph *b)
{
	int	i;
	int	j;

	i = -1;
	while(b->ways[++i])
	{
		j = b->ways[i]->length;
		while (j > 0)
		{
			if (b->ways[i]->room[j]->ant)
				ft_printf("L%d-%s ", b->ways[i]->room[j]->ant, b->ways[i]->room[j]->name);
			j--;
		}
	}
	ft_printf("\n");
	return (1);
}
