/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_swap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 13:55:29 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 15:04:49 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, size_t size)
{
	char	*tmp;

	if (size > 10)
	{
		if (!(tmp = malloc(size)))
			return ;
		ft_memcpy(tmp, b, size);
		ft_memcpy(b, a, size);
		ft_memcpy(a, tmp, size);
		free(tmp);
		return ;
	}
	while (size > sizeof(tmp))
	{
		ft_memcpy((void *)&tmp, b, sizeof(tmp));
		ft_memcpy(b, a, sizeof(tmp));
		ft_memcpy(a, (void *)&tmp, sizeof(tmp));
		size -= sizeof(tmp);
	}
	ft_memcpy((void *)&tmp, b, size);
	ft_memcpy(b, a, size);
	ft_memcpy(a, (void *)&tmp, size);
}
