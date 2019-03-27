/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_binary.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 12:15:50 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 19:25:02 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

char	*big_endian_string(int n, int size, int new, int *len)
{
	static char		s[24] = {0};
	static int		i = 0;

	if (new)
	{
		i = 0;
		ft_memset(s, '\0', 24);
	}
	if (size == 1)
		s[i++] = (char)n;
	else if (size == 2)
	{
		s[i++] = (char)(n >> 8);
		s[i++] = (char)n;
	}
	else if (size == 4)
	{
		s[i++] = (char)(n >> 24);
		s[i++] = (char)(n >> 16);
		s[i++] = (char)(n >> 8);
		s[i++] = (char)n;
	}
	if (len)
		*len = i;
	return (s);
}

int		big_endian_int(int int4)
{
	return (((int4 & 0x000000ff) << 24)
		| ((int4 & 0x0000ff00) << 8)
		| ((int4 & 0x00ff0000) >> 8)
		| ((int4 & 0xff000000) >> 24));
}

short	big_endian_short(short int2)
{
	return (((int2 & 0x00ff) << 8)
		| ((int2 & 0xff00) >> 8));
}
