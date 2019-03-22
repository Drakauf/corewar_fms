/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcrep.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 13:29:04 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 13:29:19 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memcrep(char *s, int c, int replace, int size)
{
	if ((s = ft_memchr(s, c, size)) == NULL)
		return (NULL);
	*s = replace;
	return (s);
}
