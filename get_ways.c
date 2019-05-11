#include "lem_in.h"

int	ft_get_ways(t_graph *b)
{
	int			i;

	// ft_printf("ft_get_ways,  ");
	if (ft_count_rooms_and_make_on(b) < 2)
		ft_error("ERROR: rooms are not enough in 'ft_get_ways'\n");
	// ft_printf("n_rooms = %d\n", b->n_rooms);
	if (!(ft_ways_and_buf_malloc(b)))
		ft_error("ERROR: ways malloc error in 'ft_get_ways'\n");
	i = 0;
	if (ft_check_start_links_end(b))
		ft_show_move_in_one(b);
	while(ft_end_check_for_free_links(b))
	{
		// ft_printf("\nft_get_ways in while\n");
		if (!(ft_one_way_malloc(b , i)))
			ft_error("ERROR: one ways malloc error in 'ft_get_ways'\n");
		if (ft_way_extract(b, b->ways[i]->room) == 0)
		{
			ft_freeway(b, i);
			break;
		}
		// ft_printf("\ti = %d\n", i);
		ft_get_way_length_and_expr(b, b->ways[i], i);
		// ft_show_way(b->ways[i]);
		i++;
	}
	i == 0 ? ft_error("ERROR: no ways were found in 'ft_get_ways'\n") : 0;
	return(i);
}

int		ft_check_start_links_end(t_graph *b)
{
	t_link	*lnk;
	int		i;

	i = 1;
	if ((lnk = b->start->link))
	{
		while (lnk)
		{
			if (lnk->room == b->end)
				return (1);
			lnk = lnk->next;
			i = 0;
		}
	}
	return(i);
}

int ft_end_check_for_free_links(t_graph *b)
{
	t_link *lnk;
	int i;

	// ft_printf("ft_end_check\t");
	i = 0;
	lnk = b->end->link;
	while(lnk && lnk->room)
	{
		// ft_printf("[%s]status= %d\t", lnk->room->name, lnk->room->on_off);
		if (lnk->room->on_off == on)
			i++;
		lnk = lnk->next;
	}
	// ft_printf("\n");
	return (i);
}

int	ft_way_extract(t_graph *b, t_room **room)
{
	t_room	*tmp;
	int		i;

	// ft_printf("ft_way_extract \n");
	tmp = b->rms;
	while(tmp)
	{
		tmp->parent = NULL;
		tmp = tmp->next;
	}
//	b->start->parent = b->start;
	b->end->parent = b->end;
	ft_buf_clean(b);
	if (ft_bfs(b) == 0)
		return(0);
	//writing in *way **room by parentness
	tmp = b->start;
	i = 0;
	while(tmp)
	{
		room[i] = tmp;
		if (tmp == b->end && ft_send_end(b, &room[i]))
			break;
		if (i != 0)
			tmp->on_off = off;
		tmp = tmp->parent;
		i++;
	}
	// delete way from graph
	// i = 0;
	// // ft_printf("Cleaning : ");
	// while(room[++i] != b->end)
	// {
	// 	room[i]->on_off = off;
	// 	// ft_printf("{%s>>%d} ", room[i]->name, room[i]->on_off);
	// }
	return(1);
}

int ft_send_end(t_graph *b, t_room **room)
{
	room[0] = (t_room*)ft_memalloc(sizeof(t_room));
	room[0]->name = b->end->name;
	room[0]->x = b->end->x;
	room[0]->y = b->end->y;
	room[0]->next = b->end->next;
	room[0]->link = b->end->link;
	room[0]->parent = b->end->parent;
	room[0]->on_off = on;
	return (1);
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
