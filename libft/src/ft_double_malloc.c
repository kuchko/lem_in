#include "libft.h"

void		**ft_double_malloc(size_t size, size_t y, size_t x)
{
	void	**ukz;
	size_t	i;

	if ((ukz = ft_memalloc(sizeof(void*) * (y))) == NULL)
		return (NULL);
	i = 0;
	while (i < y)
	{
		if ((ukz[i] = ft_memalloc(size * (x))) == NULL)
			return (NULL);
		i++;
	}
	return (ukz);
}
