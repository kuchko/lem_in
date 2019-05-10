#include "lem_in.h"

int	ft_count_rooms_and_make_on(t_graph *b)
{
	t_room	*tmp;

	tmp = b->rms;
	while(tmp && ++b->n_rooms)
	{
		tmp->on_off = on;
		tmp = tmp->next;
	}
	return (b->n_rooms);
}

int	ft_ways_and_buf_malloc(t_graph *b)
{
	if (!(b->ways = (t_way**)ft_memalloc((b->n_rooms + 1) * sizeof(t_way*))))
		return(0);
	if (!(b->buf = (t_room**)ft_memalloc((b->n_rooms + 1) * sizeof(t_room*))))
		return(0);
	return(1);
}

int ft_one_way_malloc(t_graph *b, int i)
{
	if (!(b->ways[i] = (t_way*)ft_memalloc(sizeof(t_way))))
		return (0);
	if (!(b->ways[i]->room = (t_room**)ft_memalloc(sizeof(t_room*) * (b->n_rooms + 1))))
		return (0);
	return (1);
}

void ft_get_way_length_and_expr(t_graph *b, t_way *way, int i)
{
	t_room	**tmp;
	int		j;

	tmp = way->room;
	way->length = -1;
	while(tmp[++way->length])
		;
	way->length--;

	// count expresion
	way->expr = 0;
	j = -1;
	if (i > 0)
		while (++j < i)
			way->expr += b->ways[i]->length - b->ways[j]->length;
}

void ft_freeway(t_graph *b, int i)
{
	free(b->ways[i]->room);
	free(b->ways[i]);
	b->ways[i] = NULL;
}
