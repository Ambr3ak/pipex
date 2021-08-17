#include "../inc/pipex.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)b;
	while (len-- > 0)
		*tmp++ = (unsigned char)c;
	return (b);
}
