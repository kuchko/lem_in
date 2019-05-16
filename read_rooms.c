/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:11:34 by okuchko           #+#    #+#             */
/*   Updated: 2019/05/13 14:11:36 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_get_rooms_n_links(int fd, t_graph *b)
{
	int		i;

	i = 0;
	while (get_next_line(fd, &(b->l)) > 0 && ++i)
	{
		if (b->l[0] == '#')
		{
			if (b->l[1] == '#' && ft_get_room_start_or_fin(b, &(b->l), fd) == 0)
				ft_error("ERROR\n");
		}
		else if (ft_get_room(b, b->l, normal) == 0)
		{
			if ((b->f_rooms = b->start && b->end ? 1 : 0) == 0)
				return (0);
			ft_get_links(fd, b->l, b);
			break ;
		}
		free(b->l);
	}
	if (b->f_rooms && b->f_links)
		return (1);
	return (0);
}

int		ft_get_room_start_or_fin(t_graph *b, char **l, int fd)
{
	t_align	al;

	if (l[0][2] && (!(ft_strcmp(&l[0][2], "start")) ||
							!(ft_strcmp(&l[0][2], "end"))))
	{
		al = ft_strcmp(&l[0][2], "start") ? end : start;
		if ((al == start && b->start) || (al == end && b->end))
			ft_error("ERROR: dublicate of start or end\n");
		free(*l);
		if (get_next_line(fd, l) < 1)
			return (0);
		if (ft_get_room(b, *l, al) == 0)
			return (0);
	}
	return (1);
}

int		ft_get_room(t_graph *b, char *l, t_align al)
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
		if (!(new = ft_room_add(b, c[0], c[1], c[2])))
			ft_error("ERROR: add room failed in 'ft_room_add'\n");
		if (al == start)
			b->start = new;
		if (al == end)
			b->end = new;
	}
	else
		i = 0;
	ft_strdoublefree(c);
	return (i);
}

t_room	*ft_room_add(t_graph *base, char *name, char *x_new, char *y_new)
{
	int		x;
	int		y;
	t_room	*tmp;
	t_room	*new;

	x = ft_atoi(x_new);
	y = ft_atoi(y_new);
	if (ft_check_dublications(base, name, x, y) == 0)
		return (NULL);
	if (!(new = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	new->name = ft_strdup(name);
	new->x = x;
	new->y = y;
	if ((tmp = base->rms))
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		base->rms = new;
	return (new);
}

int		ft_check_dublications(t_graph *base, char *name, int x, int y)
{
	t_room	*tmp;

	tmp = base->rms;
	while ((tmp))
	{
		if (ft_strcmp(name, tmp->name) == 0 || (tmp->x == x && tmp->y == y))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
