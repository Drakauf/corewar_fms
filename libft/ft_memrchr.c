/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/17 20:59:06 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/19 21:47:07 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static t_longword	ft_repeat_c(int c)
{
	t_longword repeated_c;

	repeated_c = (c | c << 8);
	repeated_c |= repeated_c << 16;
	repeated_c |= repeated_c << 32;
	return (repeated_c);
}

static void			*get_chr(t_byte *ptr, t_byte c)
{
	if (ptr[7] == c)
		return ((void *)ptr + 7);
	if (ptr[6] == c)
		return ((void *)ptr + 6);
	if (ptr[5] == c)
		return ((void *)ptr + 5);
	if (ptr[4] == c)
		return ((void *)ptr + 4);
	if (ptr[3] == c)
		return ((void *)ptr + 3);
	if (ptr[2] == c)
		return ((void *)ptr + 2);
	if (ptr[1] == c)
		return ((void *)ptr + 1);
	return ((void *)ptr);
}

static void			*memchr_no_align(const t_byte *str, int c, size_t n)
{
	while (n)
	{
		if (*(t_byte *)str == (t_byte)c)
			return ((void *)(str));
		--str;
		--n;
	}
	return (NULL);
}

void				*ft_memrchr(const void *str, int c, size_t n)
{
	const t_longword	black_hole = 0x8080808080808080L;
	const t_longword	repeat_one = 0x0101010101010101L;
	const t_longword	c64 = ft_repeat_c(c);
	t_longword			word;

	if (!n)
		return (NULL);
	str += n - 1;
	while (((t_longword)(str) % sizeof(t_longword)) != 0)
	{
		if (*((t_byte *)str) == (t_byte)c)
			return ((void *)str);
		if (!--n)
			return (NULL);
		--str;
	}
	while (n >= 8)
	{
		word = *((t_longword *)(long)(str - 7)) ^ c64;
		if (((word - repeat_one) & ~(word) & black_hole) != 0)
			return (get_chr((t_byte *)str - 7, (t_byte)c));
		str -= 8;
		n -= 8;
	}
	return (memchr_no_align((const t_byte *)str, c, n));
}
