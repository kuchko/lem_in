#include "lem_in.h"

int	ft_get_ways(t_graph *b)
{
	t_room *tmp;

	tmp = b->rms;
	while(tmp && ++b->n_rooms)
		tmp = tmp->next;
	if (!(b->way = ft_memalloc(sizeof(t_way) * b->n_rooms)))
		ft_error("ERROR\n");
	ft_printf("n_rooms = %d\n", b->n_rooms);

	return(1);
}
