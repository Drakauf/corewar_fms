/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   update_current_addr.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:14:44 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 19:15:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern void		update_current_addr(t_data *d)
{
	int				i;
	int				j;
	int				*fmt;

	fmt = d->current->fmt;
	i = 0;
	d->cur_addr += g_binsize[d->current->type].param_byte + 1;
	while (*fmt)
	{
		j = d->current->fmt[i] - 1;
		d->cur_addr += g_binsize[d->current->type].opsize[i][j];
		i++;
		fmt++;
	}
}
