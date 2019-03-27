/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ltoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 12:06:57 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/15 17:16:00 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char				*long_to_ascii(t_ulong n, char *s, int negative)
{
	while (1)
	{
		*(--s) = (n % 10) + 48;
		n /= 10;
		if (!n)
			break ;
	}
	if (negative)
		*(--s) = '-';
	return (s);
}

extern inline char		*ft_ltoa(long n)
{
	static char	tmp[21] = {0};
	int			negative;
	t_ulong		number;

	if (n < 0)
	{
		negative = 1;
		number = (t_ulong)~n + 1;
	}
	else
	{
		number = (t_ulong)n;
		negative = 0;
	}
	return (long_to_ascii(number, tmp + 19, negative));
}
