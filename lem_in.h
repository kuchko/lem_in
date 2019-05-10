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

typedef enum			e_on_off
{
	off, on
}						on_off;

typedef struct	s_graph
{
	struct s_room	*rms;
	struct s_room	*start;
	struct s_room	*end;
	int				f_rooms;
	int				f_links;
	int				ants;
	int				ants_start;
	int				ants_end;
	char			*l;

	int				n_rooms;
	struct s_way	**ways;
	int				n_ways;
	struct s_room	**buf;
}					t_graph;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
	struct s_link	*link;

	struct s_room	*parent;
	on_off			on_off;
	int				ant;

}					t_room;

typedef struct	s_link
{
	struct s_room	*room;
	struct s_link	*next;
}					t_link;

typedef struct	s_way
{
	struct s_room	**room;
	int				length;
	int				expr;


}					t_way;

int		ft_read_valid(t_graph **base, int argc, char **argv);
int		ft_get_ants(int fd);
int		ft_get_rooms_n_links(int fd, t_graph *base);

//int		ft_get_rooms(int fd, t_graph *base);
// int		ft_get_rooms(int fd, char **l, t_graph *base);
int		ft_get_room(t_graph *base, char *l, t_align al);
t_room*	ft_room_add(t_graph *base, char *name, char *x_new, char *y_new);
int	ft_get_room_start_or_fin(t_graph *base, char **l, int fd);
//int		ft_check_hash(t_graph *base, char **l);

int		ft_get_links(int fd, char *l, t_graph *base);
int ft_get_link(char *stroom1, char *stroom2, t_graph *base);
int ft_add_link_to_room(t_room *room1, t_room *room2);
void	ft_show_all(t_graph *base);

int	ft_get_ways(t_graph *base);
int	ft_way_extract(t_graph *b, t_room **room);
void ft_show_way(t_way *way);
void ft_show_ways(t_graph *base);
int	ft_bfs(t_graph *b);
void ft_buf_clean(t_graph *b);
int ft_end_check(t_graph *b);
int		ft_check_start_links_end(t_graph *b);

int	ft_count_rooms_and_make_on(t_graph *b);
int	ft_ways_and_buf_malloc(t_graph *b);
int ft_one_way_malloc(t_graph *b, int i);
void ft_get_way_length_and_expr(t_graph *b, t_way *way, int i);
void ft_freeway(t_graph *b, int i);

int		ft_move_ants(t_graph *b);
int		ft_move_ants_in_way(t_graph *b, int i);
int		ft_show_move(t_graph *b);

#endif
