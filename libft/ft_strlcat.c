/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/19 15:02:36 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/19 20:50:17 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	const size_t	srcl = ft_strlen(src);
	const size_t	dstl = ft_strlen(dst);

	if (dstl >= n)
		return (n + srcl);
	n -= dstl;
	if (n > srcl)
		n = srcl;
	else if (n > 0)
		n--;
	ft_memmove(dst + dstl, src, n);
	dst[dstl + n] = '\0';
	return (srcl + dstl);
}
