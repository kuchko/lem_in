#include "lem_in.h"

int ft_get_rooms(int fd, char **l, t_graph *base)
{
	int i;

	i = 1;
	while(ft_strlen(*l) > 0 && i > 0)
	{


///////////////			RE DO!



		if (l[0] == '#' && ft_check_hash(fd, base, *l) == 0)
			return(0); // do i need this
		else if (ft_count_char(*l, ' ') == 2)
			if (ft_get_room(base, *l, none) == 0)
				return(0);
		else
			break ;
		free(l); // ?
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

	i = 0;
	if ((c = ft_strsplit(l, ' ')) == NULL)
		return (0);
	while (c[i])
		i++;
	if (i == 3 && c[0][0] != 'L')
	{
		if (!(new = ft_room_add(base, c[0], c[1], c[2])))
			i = 0;
		else
		{
			if (al == start)
				if (base->start)
					i = 0;
				else
					base->start = new;
			if (al == end)
				if (base->end)
					i = 0;
				else
					base->end = new;
			// i = ((al == start && base->start) ? 0 : i);
			// base->start = ((al == start && !base->start) ? new : base->start);
			// i = ((al == end && base->end) ? 0 : i);
			// base->end = ((al == end && !base->end) ? new : base->end);
		}
	}
	else
		i = 0;
	ft_strdoublefree(c);
	return (i);
}



int	ft_check_hash(int fd, t_graph *base, char *l)
{
	int		i;
	char	*tmp;
	t_align	al;

	if (l[1] == '#')
	{
		if (l[2] && (!(ft_strcmp(&l[2], "start")) || !(ft_strcmp(&l[2], "end"))))
		{
			al = ft_strcmp(&l[2], "start") ? end : start;
			if (get_next_line(fd, &tmp) > -1)
			{
				i = ft_get_room(base, l, al);
				free(tmp);
				return (i);
			}
		}
	}
	return (1);
}

