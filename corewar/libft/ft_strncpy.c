/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/19 14:23:45 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/19 16:12:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	const size_t	srcsize = ft_strnlen(src, n);

	if (srcsize != n)
		ft_memset(dst + srcsize, '\0', n - srcsize);
	return (ft_memcpy(dst, src, srcsize));
}
