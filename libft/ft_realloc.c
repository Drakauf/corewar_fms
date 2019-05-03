/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 16:21:51 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 16:25:13 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, int plen, int nlen)
{
	void	*new;

	new = malloc(nlen);
	ft_memmove(new, ptr, plen);
	free(ptr);
	return (new);
}
