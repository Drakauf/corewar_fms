/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mov_addr_syntax.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 12:04:39 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

extern int	set_mov_addr_syntax(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	char			*s;

	if (t->type != LLDI)
		t->type = (i == 1) ? STI : LDI;
	if ((s = check_mov_arg1(c->s + 1, c, d, t->fmt + i)) == NULL)
		return (i);
	i++;
	check_mov_arg2(s, c, d, t->fmt + i);
	return (i);
}
