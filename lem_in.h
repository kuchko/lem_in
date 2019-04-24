#ifndef LEM_IN
# define LEM_IN

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>

typedef struct	s_fdf_iso
{
	double		x;
	double		y;
	double		z;
}				t_iso;

typedef struct	s_fdf_nod
{
	int			x;
	int			y;
	int			z;
	int			argb;
}				t_nod;


#endif
