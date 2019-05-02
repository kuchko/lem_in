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
	if (!(ft_get_rooms_n_links(fd, base)))
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

int	ft_get_rooms_n_links(int fd, t_graph **base)
{
	//int i; //?
	char *l;
	char **m;

	m = &l;
	//i = 0;


	if (ft_get_rooms(fd, m, *base))
		ft_get_links(fd, m, *base);

	// free(m);

	// if (get_next_line(fd, &l) > 0)
	// {
	// 	if (l && ft_get_rooms(fd, &l, *base))
	// 	{
	// 		//ft_show_all(*base);
	// 		ft_get_links(fd, &l, *base);
	// 	}
	// 	free(l);
	// }

	// while(get_next_line(fd, &l) > 0 && ++i)
	// {
	// 	// if (ft_strlen(l) == 0)
	// 	// 	break ;
	// 		if ((*base)->f_links == 0)
	// 		ft_get_rooms(fd, *base, l);
	// 	free(l);
	// }
	// //i > 0 ? free(l) : 0;

//	if ((*base)->f_start && (*base)->f_end && (*base)->f_rooms && (*base)->f_links)
	if ((*base)->f_rooms && (*base)->f_links)
		return (1);
	// else
	// 	free_lists();
	return (0);
}



void	ft_show_all(t_graph *base)
{
	t_room *tmp;

	ft_printf("					show all: ants=> %d", base->ants);



	tmp = base->rms;
	while(tmp)
	{
		ft_printf("|  name = %s; x = %d; y = %d  ", tmp->name, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	if(base->start)
		ft_printf("START >>> name = %s; x = %d; y = %d  ", base->start->name, base->start->x, base->start->y);
	if(base->end)
		ft_printf("| END >>> name = %s; x = %d; y = %d  ", base->end->name, base->end->x, base->end->y);
	ft_printf("\n");
}
