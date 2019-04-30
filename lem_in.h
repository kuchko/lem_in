#ifndef LEM_IN
# define LEM_IN

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>

typedef enum			e_align
{
	none, normal, start, end
}						t_align;

typedef struct	s_graph
{
	struct s_room	*rms;
	struct s_room	*start;
	struct s_room	*end;
	// int				f_start;
	// int				f_end;
	int				f_rooms;
	int				f_links;

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
int		ft_get_rooms_n_links(int fd, t_graph **base);

int		ft_get_rooms(int fd, char **l, t_graph *base);
int		ft_get_room(t_graph *base, char *l, t_align al);
t_room*	ft_room_add(t_graph *base, char *name, char *x_new, char *y_new);
int		ft_check_hash(t_graph *base, char **l);

int		ft_get_links(int fd, char **l, t_graph *base);

void	ft_show_all(t_graph *base);

#endif
