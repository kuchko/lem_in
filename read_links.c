#include "lem_in.h"

int ft_get_links(int fd, char **l, t_graph *base)
{
	int i;
	ft_printf("ft_get_links got next => %s\n", base->tmp);
	if (l[0][0] == (char)fd)
		i = 2;

	base->f_links = 1;
	return(base->f_links);
}
