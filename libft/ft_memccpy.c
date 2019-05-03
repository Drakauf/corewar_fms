/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/17 16:15:14 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 21:32:00 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *srcp1, const void *srcp2, int c, size_t len)
{
	void *cp;

	if ((cp = ft_memchr(srcp2, c, len)) != NULL)
		return (ft_mempcpy(srcp1, srcp2, (cp - srcp2 + 1)));
	ft_memcpy(srcp1, srcp2, len);
	return (NULL);
}
