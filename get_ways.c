#include "lem_in.h"

void ft_show_ways(t_graph *b)
{
	int i;

	if (b->way)
	{
		i = 0;
		while((b->way[i] != NULL))
			ft_show_way(&b->way[i]);
	}
}

void ft_show_way(t_way *way)
{
	int i;

	i = -1;
	while (way->room[++i])
		ft_printf(" %d>[%s];", i, way->room[i]->name);
	ft_printf("\n");
}

int	ft_get_ways(t_graph *b)
{
	t_room		*tmp;
	int			i;

	ft_printf("ft_get_ways,  ");
	tmp = b->rms;
	while(tmp && ++b->n_rooms)
	{
		tmp->on_off = on;
		tmp = tmp->next;
	}
	if (!(b->way = (t_way*)ft_memalloc(sizeof(t_way) * (b->n_rooms + 1))))
		ft_error("ERROR: malloc error 'ft_get_ways'\n");
	b->buf = (t_room**)ft_memalloc(sizeof(t_room*) * (b->n_rooms + 1));
	ft_printf("n_rooms = %d\n", b->n_rooms);
	i = 0;
	///check for start->end
	while((i < b->n_rooms) && ft_start_check(b))
	{
		ft_printf("\nft_get_ways in while\n");
		b->way[i].room = (t_room**)ft_memalloc(sizeof(t_room*) * (b->n_rooms + 1));
		if (ft_way_extract(b, b->way[i].room) == 0)
			break;
		ft_printf("\ti = %d\n", i);
		ft_show_way(&b->way[i]);

//		b->way[i].length = ft_get_way_lenth(b->way[i].room);
//		b->way[i].expr = i > 0 ? b->way[i].length - b->way[i - 1].length : 0;
		i++;
	}
	i == 0 ? ft_error("ERROR: no ways were found 'ft_way_extract'\n") : 0;
	return(i);
}

int ft_start_check(t_graph *b)
{
	// t_room	*tmp;
	t_link *lnk;
	int i;

	ft_printf("ft_start_check\t");
	i = 0;
	lnk = b->start->link;
	while(lnk && lnk->room)
	{
		ft_printf("[%s]status= %d\t", lnk->room->name, lnk->room->on_off);
		if (lnk->room->on_off == on)
			i++;
		lnk = lnk->next;
	}
	ft_printf("\n");
	return (i);
}

int	ft_way_extract(t_graph *b, t_room **room)
{
	t_room	*tmp;
	int		i;

	ft_printf("ft_way_extract \n");
	tmp = b->rms;
	while(tmp)
	{
		tmp->parent = NULL;
		tmp = tmp->next;
	}
	b->start->parent = b->start;
	// b->end->parent = b->end;
	ft_buf_clean(b);
	if (ft_bfs(b) == 0)
		return(0);
	//writing in *way **room by parentness
	tmp = b->end;
	i = 0;
	while(tmp)
	{
		room[i++] = tmp;
		if (tmp == b->start)
			break;
		tmp = tmp->parent;
	}
	// delete way from graph
	i = 0;
	ft_printf("Cleaning : ");
	while(room[++i] != b->start)
	{
		room[i]->on_off = off;
		ft_printf("{%s>>%d} ", room[i]->name, room[i]->on_off);
	}
	return(1);
}

int	ft_bfs(t_graph *b)
{
	t_room	*tmp;
	t_link	*t;
	int		i;
	int		j;

	ft_printf("ft_bfs: ");
	tmp = b->start;
	b->buf[0] = tmp;
	i = 0;
	j = 1;
	while(tmp && tmp != b->end) // (tmp)
	{
		ft_printf("[%s] ", tmp->name);
		if ((tmp->on_off == on) && (t = tmp->link))
			while(t)
			{
				if (t->room->parent == NULL && (t->room->on_off == on))
				{
					t->room->parent = tmp;
					if (t->room->parent == b->end)
					{
						ft_printf("out 1");
						return(1);
					}
					b->buf[j++] = t->room;
				}
				t = t->next;
			}
		tmp = b->buf[++i];
	}
	if (tmp == b->end)
		ft_printf("debug %d", i);
	return (tmp == b->end ? i : 0);
}

void ft_buf_clean(t_graph *b)
{
	int	i;

	if (b->n_rooms > 0)
	{
		i = 0;
		while(i < b->n_rooms + 1)
			b->buf[i++] = NULL;
	}
}
