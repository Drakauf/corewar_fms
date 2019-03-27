/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 16:31:10 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/23 16:33:23 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void *srcaddr, size_t size)
{
	void *cpy;

	if ((cpy = malloc(size)) == NULL)
		return (NULL);
	return (ft_memcpy(cpy, srcaddr, size));
}
