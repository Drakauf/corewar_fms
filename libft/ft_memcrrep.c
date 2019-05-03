/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcrrep.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/11 22:54:40 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/11 22:55:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memcrrep(char *s, int c, int replace, int size)
{
	if ((s = ft_memrchr(s, c, size)) == NULL)
		return (NULL);
	*s = replace;
	return (s);
}
