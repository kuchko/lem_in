#include "lem_in.h"

t_room*	ft_room_add(t_graph *base, char *name, char *x_new, char *y_new)
{
	int		x;
	int		y;
	t_room	*tmp;
	t_room	*new;

	x = ft_atoi(x_new);
	y = ft_atoi(y_new);
	tmp = base->rms;
	while(tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0 || (tmp->x == x && tmp->y == y))
			return (NULL);
		tmp = tmp->next;
	}
	if (!(new = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	if (tmp = base->rms)
	{
		while(tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		base->rms = new;
	return (new);
}

