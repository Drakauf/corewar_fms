/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/19 22:16:45 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 13:52:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int			memcmp_byte(const t_byte *p1, const t_byte *p2)
{
	if (*p1 != *p2 || !*p1)
		return ((*p1 - *p2));
	if (p1[1] != p2[1] || !p1[1])
		return ((p1[1] - p2[1]));
	if (p1[2] != p2[2] || !p1[2])
		return ((p1[2] - p2[2]));
	if (p1[3] != p2[3] || !p1[3])
		return ((p1[3] - p2[3]));
	if (p1[4] != p2[4] || !p1[4])
		return ((p1[4] - p2[4]));
	if (p1[5] != p2[5] || !p1[5])
		return ((p1[5] - p2[5]));
	if (p1[6] != p2[6] || !p1[6])
		return ((p1[6] - p2[6]));
	return ((p1[7] - p2[7]));
}

extern inline int	ft_strcmp(const char *s1, const char *s2)
{
	t_longword		word;
	register int	result;

	while (((t_longword)s1 & 0x7L))
	{
		if ((result = *(t_byte*)s1 != *(t_byte*)s2) || !*s1)
			return (result);
		s1++;
		s2++;
	}
	while (1)
	{
		word = *(t_longword*)s1;
		if (word != *(t_longword*)s2
				|| ((word - REPEAT_ONE) & ~word & BLACK_HOLE) != 0)
		{
			break ;
		}
		s1++;
		s2++;
	}
	return (memcmp_byte((const t_byte *)s1, (const t_byte *)s2));
}
