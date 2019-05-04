#include "lem_in.h"

int ft_get_links(int fd, char *l, t_graph *base)
{
	char **c;
	int i;
	int k;

	ft_printf("ft_get_links: string to work => %s\n", l);
	i = -1;
	k = 0;
	while(ft_strlen(l) && ++k)
	{
		ft_printf("ft_get_links: in while  => %s\n", l);
		i = 0;
		if ((c = ft_strsplit(l, '-')) == NULL)
			ft_error("ERROR\n");
		while(c[i])
			i++;
		if (i == 2)
			i = ft_get_link(c[0], c[1], base);
		ft_strdoublefree(c);
		if (i != 2)
			break;
		free(l);
		base->f_links = 1;
		get_next_line(fd, &l);
	}
//	free(l);
	k > 0 ? free(l) : 0;
//	base->f_links = i > 0 ? 1 : 0;
	return(base->f_links);
}

int ft_get_link(char *stroom1, char *stroom2, t_graph *base)
{
	t_room *room1;
	t_room *room2;

	ft_printf("ft_get_link\n");
	if (ft_strcmp(stroom1, stroom2) == 0)
		return (0);
	room1 = base->rms;
	while (room1 && ft_strcmp(room1->name, stroom1) != 0)
		room1 = room1->next;
	room2 = base->rms;
	while (room2 && ft_strcmp(room2->name, stroom2) != 0)
		room2 = room2->next;
	if (room1 && room2)
		if (ft_add_link_to_room(room1, room2)
				&& ft_add_link_to_room(room2, room1))
			return (2);
	return (0);
}

int ft_add_link_to_room(t_room *room1, t_room *room2)
{
	t_link	*ptr_link;
	t_link	*tmp_link;

	ft_printf("ft_add_link_to_room %p %s %p %s\n", room1, room1->name, room2, room2->name);
	if (!(ptr_link = room1->link))
	{
		if (!(room1->link = (t_link*)ft_memalloc(sizeof(t_link))))
			ft_error("ERROR\n");
		room1->link->room = room2;
		room1->link->next = NULL; // not neccessary
		return(1);
	}
	ft_printf("	ft_add_link_to_room DEBUG\n");

	tmp_link = room1->link;
	while(tmp_link && tmp_link->next)
	{
		if (tmp_link->room == room2)
			ft_error("ERROR\n");
		tmp_link = tmp_link->next;
	}
	if (!(ptr_link = (t_link*)ft_memalloc(sizeof(t_link))))
		ft_error("ERROR\n");
	ptr_link->room = room2;
	tmp_link->next = ptr_link;
	return (1);
}
