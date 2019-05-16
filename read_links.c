/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:11:24 by okuchko           #+#    #+#             */
/*   Updated: 2019/05/13 14:11:27 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_get_links(int fd, char *l, t_graph *base)
{
	char	**c;
	int		i;
	int		k;

	k = 0;
	while (ft_strlen(l) && ++k)
	{
		i = 0;
		if (l[0] != '#')
		{
			if ((c = ft_strsplit(l, '-')) == NULL)
				ft_error("ERROR: bad string in reading links 'ft_get_links'\n");
			while (c[i])
				i++;
			i == 2 ? i = ft_get_link(c[0], c[1], base) : 0;
			ft_strdoublefree(c);
			if (i != 2)
				break ;
		}
		free(l);
		base->f_links = 1;
		get_next_line(fd, &l);
	}
	k > 0 ? free(l) : 0;
	return (base->f_links);
}

int	ft_get_link(char *stroom1, char *stroom2, t_graph *base)
{
	t_room	*room1;
	t_room	*room2;

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

int	ft_add_link_to_room(t_room *room1, t_room *room2)
{
	t_link	*ptr_link;
	t_link	*tmp_link;

	if (!(ptr_link = room1->link))
	{
		if (!(room1->link = (t_link*)ft_memalloc(sizeof(t_link))))
			ft_error("ERROR: malloc error in 'ft_add_link_to_room'\n");
		room1->link->room = room2;
		room1->link->next = NULL;
		return (1);
	}
	tmp_link = room1->link;
	while (tmp_link && tmp_link->next)
	{
		if (tmp_link->room == room2)
			ft_error("ERROR: link dublication 'ft_add_link_to_room'\n");
		tmp_link = tmp_link->next;
	}
	if (!(ptr_link = (t_link*)ft_memalloc(sizeof(t_link))))
		ft_error("ERROR: malloc error in 'ft_add_link_to_room'\n");
	ptr_link->room = room2;
	tmp_link->next = ptr_link;
	return (1);
}
