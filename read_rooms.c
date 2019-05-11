#include "lem_in.h"

int	ft_get_rooms_n_links(int fd, t_graph *base)
{
	int		i;

	i = 0;
	while(get_next_line(fd, &(base->l)) > 0 && ++i)
	{
		if (base->l[0] == '#')
		{
			if (base->l[1] == '#' && ft_get_room_start_or_fin(base, &(base->l), fd) == 0)
				ft_error("ERROR\n");
		}
		else if (ft_get_room(base, base->l, normal) == 0)
		{
			if ((base->f_rooms = base->start && base->end ? 1 : 0) == 0)
				return (0);
			ft_get_links(fd, base->l, base);
			break;
		}
		free(base->l);
	}
	if (base->f_rooms && base->f_links)
		return (1);
	return (0);
}



int			ft_get_room(t_graph *base, char *l, t_align al)
{
	char	**c;
	int		i;
	t_room	*new;

	i = 0;
	if ((c = ft_strsplit(l, ' ')) == NULL)
		ft_error("ERROR: malloc in 'ft_get_room'\n");
	while (c[i])
		i++;
	if (i == 3 && c[0][0] != 'L')
	{
		if (!(new = ft_room_add(base, c[0], c[1], c[2])))
			ft_error("ERROR: read room faild in 'ft_room_add'\n");
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

	if (l[0][2] && (!(ft_strcmp(&l[0][2], "start")) || !(ft_strcmp(&l[0][2], "end"))))
	{
		al = ft_strcmp(&l[0][2], "start") ? end : start;
		if ((al == start && base->start) || (al == end && base->end))
			ft_error("ERROR: dublicate of start or end\n");
		free(*l);
		if (get_next_line(fd, l) < 1)
			return (0);
		if (ft_get_room(base, *l, al) == 0)
			return (0);
	}
	return (1);
}
