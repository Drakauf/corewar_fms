
#include "libft.h"

extern int		ft_ishexa(int c, int maj)
{
	if (maj == 1)
		return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
	if (maj == 2)
		return ((c >= '0' && c <= '9')
			|| (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'));
}
