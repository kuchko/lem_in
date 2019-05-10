#include "lem_in.h"

void	ft_show_all(t_graph *base)
{
	t_room *tmp;
	t_link *lnk;

	ft_printf("					show all: ants=> %d\n", base->ants);
	tmp = base->rms;
	while(tmp)
	{
		if(tmp == base->start)
			ft_printf("START >>> ");
		else if(tmp == base->end)
			ft_printf("END >>> ");
		ft_printf("name = %s; x = %d; y = %d ", tmp->name, tmp->x, tmp->y);
		if ((lnk = tmp->link))
		{
			ft_printf("| LINKS :: ");
			while(lnk && lnk->room)
			{
				ft_printf("L%s-%s | ", tmp->name, lnk->room->name);
				lnk = lnk->next;
			}
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("\n");
}


void ft_show_ways(t_graph *b)
{
	int i;


	if (b->ways)
	{
		i = 0;
		ft_printf("\nWAYS:\n\n");
		while((b->ways[i]))// && b->ways[i]->length)
		{
			ft_printf("#%d, ", i);
			ft_show_way(b->ways[i++]);
		}
	}
}

void ft_show_way(t_way *way)
{
	int i;

	i = -1;
	ft_printf("Length = %d, ", way->length);
	ft_printf("Expression = %d\n", way->expr);
	while (way->room[++i])
		ft_printf("[%s] ", way->room[i]->name);
	ft_printf("\n");
}
