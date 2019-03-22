/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pow.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 13:12:30 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/17 18:31:47 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

extern t_ulong		ft_ten_powul(int p)
{
	t_ulong n;

	n = 10;
	if (p < 1)
		return (0);
	while (--p)
		n *= 10;
	return (n);
}
