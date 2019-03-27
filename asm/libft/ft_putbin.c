/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putbin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 19:37:00 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 19:50:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbin(long n, size_t size, t_uint lf)
{
	const t_ulong	repeat_one = 0x0101010101010100UL;
	t_ulong			curs;
	int				count;

	count = 0;
	curs = 1UL << ((size * 8) - 1);
	while (curs)
	{
		(curs & n) ? write(1, "1", 1) : write(1, "0", 1);
		if (curs & repeat_one)
		{
			write(1, " ", 1);
		}
		curs >>= 1;
	}
	while (lf)
	{
		write(1, "\n", 1);
		--lf;
	}
}
