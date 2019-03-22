/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 15:43:09 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 10:34:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nullbyte(const unsigned char *s, const unsigned char *end,
		const unsigned char *start)
{
	const unsigned long int	end_byte = (unsigned long int)(end - s);

	if (s[0] == 0)
		return (s - start);
	if (s[1] == 0 || 1 == end_byte)
		return (s - start + 1);
	if (s[2] == 0 || 2 == end_byte)
		return (s - start + 2);
	if (s[3] == 0 || 3 == end_byte)
		return (s - start + 3);
	if (s[4] == 0 || 4 == end_byte)
		return (s - start + 4);
	if (s[5] == 0 || 5 == end_byte)
		return (s - start + 5);
	if (s[6] == 0 || 6 == end_byte)
		return (s - start + 6);
	return (s - start + 7);
}

static size_t	ft_strnlen_align(unsigned long int pstr,
					const unsigned long int end,
					const unsigned long int start)
{
	const unsigned long int	repeat_one = 0x0101010101010101UL;
	const unsigned long int	black_hole = 0x8080808080808080UL;
	unsigned long int		values;

	while (pstr < end)
	{
		values = *(unsigned long int *)pstr;
		if (((values - repeat_one) & ~values & black_hole) != 0)
		{
			return (get_nullbyte((const unsigned char *)pstr,
								(const unsigned char *)end,
								(const unsigned char *)start));
		}
		pstr += 8;
	}
	return (end - (unsigned long int)start);
}

size_t			ft_strnlen(const char *str, size_t max)
{
	unsigned long int		pstr;
	unsigned long int		end;

	if (max == 0)
		return (0);
	end = (unsigned long int)str + max;
	if (end < (unsigned long int)str)
		end = ~0UL;
	pstr = (unsigned long int)str;
	while (pstr % 8 != 0)
	{
		if (*(unsigned char *)pstr != 0 && pstr < end)
			pstr += 1;
		else
			return (pstr - (unsigned long int)str);
	}
	return (ft_strnlen_align(pstr, end, (unsigned long int)str));
}
