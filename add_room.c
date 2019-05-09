#include "lem_in.h"

t_room*	ft_room_add(t_graph *base, char *name, char *x_new, char *y_new)
{
	int		x;
	int		y;
	t_room	*tmp;
	t_room	*new;

	// ft_printf("ft_room_add  ");
	x = ft_atoi(x_new);
	y = ft_atoi(y_new);
	tmp = base->rms;
	// ft_printf("got next: name = %s, x = %d, y = %d,  %p\n", name, x, y, tmp);
	while((tmp))
	{
		//ft_printf("inwhile\n");
		if (ft_strcmp(name, tmp->name) == 0 || (tmp->x == x && tmp->y == y))
			return (NULL);
		tmp = tmp->next;
	}
//	ft_printf("debug1\n");
	if (!(new = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
//	ft_printf("debug2\n");
	new->name = ft_strdup(name);
	new->x = x;
	new->y = y;
	if ((tmp = base->rms))
	{
		while(tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		base->rms = new;
	// ft_printf("put to rms after ft_room_add: \n");
	// ft_show_all(base);
	return (new);
}

