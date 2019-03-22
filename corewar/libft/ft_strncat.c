/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/19 14:44:09 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/19 17:12:08 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	const size_t	src_size = ft_strnlen(src, n);
	char			*dst_end;

	dst_end = dst + ft_strlen(dst);
	ft_memrcpy(dst_end, src, src_size);
	dst_end[src_size] = '\0';
	return (dst);
}
