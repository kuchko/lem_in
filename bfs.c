#include "lem_in.h"

int	ft_bfs(t_graph *b)
{
	t_room	*tmp;
	t_link	*t;
	int		i;
	int		j;

	// ft_printf("ft_bfs: ");
	tmp = b->end;
	b->buf[0] = tmp;
	i = 0;
	j = 1;
	while(tmp && tmp != b->start) // (tmp)
	{
		// ft_printf("[%s] ", tmp->name);
		if ((tmp->on_off == on) && (t = tmp->link))
			while(t)
			{
				if (t->room->parent == NULL && (t->room->on_off == on))
				{
					t->room->parent = tmp;
// 					if (t->room == b->start) // we can erase it
// 					{
// //						ft_printf("out 1");
// 						return(1);
// 					}
					b->buf[j++] = t->room;
				}
				t = t->next;
			}
		tmp = b->buf[++i];
	}
	// if (tmp == b->start)
	// 	ft_printf("debug %d", i);
	return (tmp == b->start ? i : 0);
}
