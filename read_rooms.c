#include "lem_in.h"

int		ft_get_rooms(int fd, char **l, t_graph *base)
{
	int i;
	t_align al;

	i = 1;

	while(ft_strlen(*l) > 0 && i > 0)
	{
//		ft_printf("ft_get_rooms in while => %s", *l);
		al = 1;
		if (l[0][0] == '#')
		{
			al = ft_check_hash(base, l);
			if (al == 0)
			{
				ft_printf("%s    ->> 1- hash failed\n", *l);
				return(0); // do i need this
			}
			free(*l);
			i = get_next_line(fd, l);
		}
		if (i > 0 && ft_count_char(*l, ' ') == 2)
		{
			ft_printf("%s    ->> 2- 2 spaces found\n", *l);
			if (ft_get_room(base, *l, al) == 0)
				return(0);
		}
		else
		{
			ft_printf("%s    ->> 3- rooms are over\n", *l);
			break ;
		}
		free(*l);// ---  pointer being freed was not allocated?
		i = get_next_line(fd, l);
	}
	base->f_rooms = base->start && base->end ? 1 : 0;
	return (base->f_rooms);
}

int			ft_get_room(t_graph *base, char *l, t_align al)
{
	char	**c;
	int		i;
	t_room	*new;

//	ft_printf("ft_get_room ==> %s align = %d\n", l, al);
	ft_printf("ft_get_room\n");
	i = 0;
	if ((c = ft_strsplit(l, ' ')) == NULL)
		return (0);
	while (c[i])
		i++;
//	ft_printf("i = %d, name, x,y = %s, %s, %s\n", i, c[0], c[1], c[2]);
	if (i == 3 && c[0][0] != 'L')
	{
		ft_printf("room is valid\n");
		if (!(new = ft_room_add(base, c[0], c[1], c[2])))
			i = 0;
		if (al == start)
			base->start = new;
		if (al == end)
			base->end = new;
	}
	else
		i = 0;
	ft_strdoublefree(c);
	return (i);
}


int	ft_check_hash(t_graph *base, char **l)
{
	t_align	al;

	al = 1;
	if (l[0][1] == '#')
	{
		ft_printf(" ft_check_hash => %s\n", &l[0][2]);
		if (l[0][2] && (!(ft_strcmp(&l[0][2], "start")) || !(ft_strcmp(&l[0][2], "end"))))
		{
			al = ft_strcmp(&l[0][2], "start") ? end : start;
			ft_printf("align = %d\n", al);
			if ((al == start && base->start) || (al == end && base->end))
				return (0);
		}
	}
	return (al);
}




int ft_get_links(int fd, char **l, t_graph *base)
{
	int i;

	if (l[0][0] == (char)fd)
		i = 2;
	// i = 1;
	// while(ft_strlen(*l) > 0 && i > 0)
	// {
	// 	if (l[0] == '#' && ft_check_hash(fd, base, *l) == 0)
	// 		return(0);
	// 	else if (ft_count_char(*l, ' ') == 2)
	// 		if (ft_get_room(base, *l, none) == 0)
	// 			return(0);
	// 	else
	// 		break ;
	// 	free(l);
	// 	i = get_next_line(fd, l);
	// }
	// base->f_rooms = base->start && base->end ? 1 : 0;
	// return (base->f_rooms);


	base->f_links = 1;
	return(base->f_links);
}
