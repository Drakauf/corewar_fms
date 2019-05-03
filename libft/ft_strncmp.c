/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncmp.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 11:04:16 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 15:52:09 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int			memcmp_8_loop(t_byte *p1, t_byte *p2, size_t n)
{
	register int	result;

	result = 0;
	while (1)
	{
		if (!n-- || (result = *p1 - *p2) || !*p1)
			return (result);
		if (!n-- || (result = p1[1] - p2[1]) || !p1[1])
			return (result);
		if (!n-- || (result = p1[2] - p2[2]) || !p1[2])
			return (result);
		if (!n-- || (result = p1[3] - p2[3]) || !p1[3])
			return (result);
		if (!n-- || (result = p1[4] - p2[4]) || !p1[4])
			return (result);
		if (!n-- || (result = p1[5] - p2[5]) || !p1[5])
			return (result);
		if (!n-- || (result = p1[6] - p2[6]) || !p1[6])
			return (result);
		if (!n-- || (result = p1[7] - p2[7]) || !p1[7])
			return (result);
		p1 += 8;
		p2 += 8;
	}
	return (0);
}

static int			memcmp_8(t_byte *p1, t_byte *p2)
{
	register int	result;

	if ((result = *p1 - *p2) || !*p1)
		return (result);
	if ((result = p1[1] - p2[1]) || !p1[1])
		return (result);
	if ((result = p1[2] - p2[2]) || !p1[2])
		return (result);
	if ((result = p1[3] - p2[3]) || !p1[3])
		return (result);
	if ((result = p1[4] - p2[4]) || !p1[4])
		return (result);
	if ((result = p1[5] - p2[5]) || !p1[5])
		return (result);
	if ((result = p1[6] - p2[6]) || !p1[6])
		return (result);
	if ((result = p1[7] - p2[7]) || !p1[7])
		return (result);
	return (0);
}

static inline int	memcmp_longword(const t_longword *s1,
						const t_longword *s2, size_t n, size_t n_word)
{
	t_longword			word;

	while (n_word)
	{
		word = *s1;
		if (*s1 != *s2 || (((word - REPEAT_ONE) & ~word & BLACK_HOLE) != 0))
		{
			return (memcmp_8((t_byte *)s1, (t_byte *)s2));
		}
		s1++;
		s2++;
		n_word--;
	}
	return (memcmp_8_loop((t_byte *)s1, (t_byte *)s2, n));
}

extern inline int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	register int	result;

	if (n > 16)
	{
		while (((t_longword)s1 % 8))
		{
			if ((result = *((t_byte *)s1) - *((t_byte *)s2)) || !*s1)
				return (result);
			s1 += 1;
			s2 += 1;
			n -= 1;
		}
		return (memcmp_longword((t_longword *)s1, (t_longword *)s2,
								n % 8, n / 8));
	}
	return (memcmp_8_loop((t_byte *)s1, (t_byte *)s2, n));
}
