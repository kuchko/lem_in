#ifndef LEM_IN
# define LEM_IN

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>


typedef struct	s_graph
{
	struct s_room	*start;
	int				ants;
}					t_graph;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
}					t_room;

typedef struct	s_link
{
	struct s_room	*room;
	struct s_link	*next;
}					t_link;


int		ft_read_valid(t_graph **base, int argc, char **argv);
int		ft_get_ants(int fd);

#endif
