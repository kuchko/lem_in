#include "lem_in.h"

///// all in --->>>  ft_get_rooms_n_links()

int ft_get_rooms(int fd, char **l, t_graph *base)
{
	int i;

	i = 1;
	while(ft_strlen(*l) > 0 && i > 0)
	{
		if (l[0] == '#' && ft_check_hash(fd, base, *l) == 0)
			return(0);
		if (ft_count_char(*l, ' ') == 2)
			if (ft_get_room(base, *l) == 0)
				return(0);
		else
			break ;
		free(l); // ?
		i = get_next_line(fd, l);
	}
	if (base->f_start && base->f_end && (base->f_rooms = 1))
		return (1);
	return (0);
}

int			ft_get_room(t_graph *base, char *l)
{
	char	**c;
	int		i;

	i = 0;
	if ((c = ft_strsplit(l, ' ')) == NULL)
		return (0);
	while (c[i])
		i++;
	if (i == 3 && c[0][0] != 'L')
	{
		if (ft_room_add(base, c[0], c[1], c[2]) == 0)
			i = 0;
	}
	else
		i = 0;
	ft_strdoublefree(c);
	return (i);
}



////////////////////////////////// just did down
int	ft_room_add(t_graph *base, char *name, char *x_new, char *y_new)
{
	int		x;
	int		y;
	t_room	*tmp;
	t_room	*new;

	x = ft_atoi(x_new);
	y = ft_atoi(y_new);
	tmp = base->start;
	while(tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0 || (tmp->x == x && tmp->y == y))
			return (0);
		tmp = tmp->next;
	}
	new = ft_memalloc(sizeof(t_room));
	if (tmp = base->start)
	{
		while(tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		base->start = new;
 	return (1);
}

int	ft_check_hash(int fd, t_graph *base, char *l)
{
	int		i;
	char	*tmp;

	if (l[0] && l[1] && l[0] == '#' && l[1] == '#')
	{
		if (l[2] && (!(ft_strcmp(&l[2], "start"))))
			if (get_next_line(fd, &tmp) > -1)
			{
				i = ft_get_room_start(base, l);
				free(tmp);
				return (i);
			}
		else if (l[2] && ft_strcmp(&l[2], "end"))
			if (get_next_line(fd, &tmp) > -1)
			{
				i = ft_get_room_end(base, l);
				free(tmp);
				return (i);
			}
//		return(1);
	}
//	return(l[0] == '#' ? 1 : 0);
	return (1);
}

