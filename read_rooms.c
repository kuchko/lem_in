#include "lem_in.h"

int		ft_get_rooms(int fd, char **l, t_graph *base)
{
//	int i;
	ft_printf("ft_get_roomS\n");
	while(get_next_line(fd, l) > 0)
	{
		ft_printf("ft_get_rooms in while => %s\n", *l);
		if (l[0][0] == '#')
		{
			ft_printf(" %s    ->> 1- hash found\n", *l);
			if (l[0][1] == '#' && ft_get_room_start_or_fin(base, l, fd) == 0)
				ft_error("ERROR\n");
		}
		else if (ft_get_room(base, *l, normal) == 0)
		{
			ft_printf(" %s    ->> 2- rooms are over\n", *l);
			base->tmp = ft_strdup(*l);
			free(*l);
			break;
		}
		free(*l);
	}
	//i > 0 ? free(l) : 0;
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
		ft_error("ERROR\n");
	while (c[i])
		i++;
//	ft_printf("i = %d, name, x,y = %s, %s, %s\n", i, c[0], c[1], c[2]);
	if (i == 3 && c[0][0] != 'L')
	{
	//	ft_printf("room is valid\n");
		if (!(new = ft_room_add(base, c[0], c[1], c[2])))
			ft_error("ERROR\n");
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



int	ft_get_room_start_or_fin(t_graph *base, char **l, int fd)
{
	t_align	al;

	ft_printf(" ft_check_hash => %s\n", &l[0][2]);
	if (l[0][2] && (!(ft_strcmp(&l[0][2], "start")) || !(ft_strcmp(&l[0][2], "end"))))
	{
		al = ft_strcmp(&l[0][2], "start") ? end : start;
		if ((al == start && base->start) || (al == end && base->end))
			return (0);
		free(*l);
		if (get_next_line(fd, l) < 1)
			return (0);
		if (ft_get_room(base, *l, al) == 0)
			return (0);
	}
	return (1);
}


// int	ft_check_hash(t_graph *base, char **l)
// {
// 	t_align	al;

// 	al = 1;
// 	if (l[0][1] == '#')
// 	{
// 		ft_printf(" ft_check_hash => %s\n", &l[0][2]);
// 		if (l[0][2] && (!(ft_strcmp(&l[0][2], "start")) || !(ft_strcmp(&l[0][2], "end"))))
// 		{
// 			al = ft_strcmp(&l[0][2], "start") ? end : start;
// 			ft_printf("align = %d\n", al);
// 			if ((al == start && base->start) || (al == end && base->end))
// 				return (0);
// 		}
// 	}
// 	return (al);
// }
