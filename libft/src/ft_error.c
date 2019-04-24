#include "libft.h"
#include "ft_printf.h"

void		ft_error(char *s)
{
	ft_printf("%s", s);
	system("leaks lem-in > leaks");
	exit(0);
}
