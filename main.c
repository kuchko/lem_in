/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 13:54:35 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/30 13:54:37 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main()
{
	t_graph	*base;

	base = ft_memalloc(sizeof(t_graph));

	if (base == NULL || !(ft_read_valid(&base)))
		ft_error("ERROR: data read error\n");
	if ((base->n_ways = ft_get_ways(base)) == 0)
		ft_error("ERROR: ways was not found");
	ft_show_ways(base);
	ft_move_ants(base);
	system("leaks lem-in > leaks");
	return (0);
}

int	ft_read_valid(t_graph **base)
{
	int		fd;

	fd = 0;
	if (!((*base)->ants = ft_get_ants(fd)))
		ft_error("ERROR: could not read ants\n");
	if (!(ft_get_rooms_n_links(fd, *base)))
		return(0);
	close(fd);
	return(1);
}

int	ft_get_ants(int fd)
{
	int res;
	char *line;
	int i;

	i = -1;
	if ((res = get_next_line(fd, &line)) == 1)
	{
		if (line[0] == '+')
			i++;
		while (line[++i])
			if (line[i] < '0' || line[i] > '9' || i > 11)
			{
				free(line);
				return (0);
			}
		res = ft_atoi(line);
	}
	if (res != -1)
		free(line);
	return(res < 1 ? 0 : res);
}

