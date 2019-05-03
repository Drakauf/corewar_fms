/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcrepall.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 13:29:48 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 17:17:24 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcrepall(char *s, int c, int replace, int size)
{
	char	*p;
	int		count;

	count = 0;
	while ((p = ft_memchr(s, c, size)))
	{
		*(p++) = replace;
		size -= (p - s);
		s = p;
		count++;
	}
	return (count);
}
