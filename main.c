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

int		main(int argc, char **argv)
{
	t_graph	*base;

	base = ft_memalloc(sizeof(t_graph));

	if (base == NULL || !(ft_read_valid(&base, argc, argv)))
		ft_error("ERROR_tut\n");
	ft_show_all(base);

	if ((base->n_ways = ft_get_ways(base)) == 0)
		ft_error("Error: ways was not found");

	system("leaks lem-in > leaks");
	return (0);
}

int	ft_read_valid(t_graph **base, int argc, char **argv)
{
	int		fd;

	if (argc == 1)
		ft_error("usage:	lem-in input_file\n");
	if (argc > 2)
		ft_error("ERROR:	lem-in must have one input_file\n");
	if ((fd = open(argv[1], O_DIRECTORY)) > 0)
		ft_error("ERROR:	open directory is invalid\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error("ERROR:	open input_file error\n");

	if (!((*base)->ants = ft_get_ants(fd)))
		return(0);
	ft_printf("ants are read = %d\n", (*base)->ants);
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

void	ft_show_all(t_graph *base)
{
	t_room *tmp;
	t_link *lnk;

	ft_printf("					show all: ants=> %d\n", base->ants);
	tmp = base->rms;
	while(tmp)
	{
		if(tmp == base->start)
			ft_printf("START >>> ");
		else if(tmp == base->end)
			ft_printf("END >>> ");
		ft_printf("name = %s; x = %d; y = %d ", tmp->name, tmp->x, tmp->y);
		if ((lnk = tmp->link))
		{
			ft_printf("| LINKS :: ");
			while(lnk && lnk->room)
			{
				ft_printf("L%s-%s | ", tmp->name, lnk->room->name);
				lnk = lnk->next;
			}
		}
		ft_printf("\n");
		tmp = tmp->next;
	}

	ft_printf("\n");
}
