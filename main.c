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
		ft_error("ERROR\n");


	system("leaks lem-in > leaks");
	return (0);
}

int	ft_read_valid(t_graph **base,int argc, char **argv)
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
		ft_error("ERROR\n");
	ft_printf("%d\n", (*base)->ants);


	close(fd);
	// if (wire->y_range > 10000)
	// 	ft_error("map is too big\n");
	// if (ft_valid_symbols(*start, wire->y_range) == 0)
	// 	ft_error("invalid symbols in file\n");
	// if (!ft_make_valid_wire(*start, wire))
	// 	ft_error("map error. coordinates might be out of range.\n");
	return(1);
}

int ft_get_ants(int fd)
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
