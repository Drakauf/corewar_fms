/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_operands_type.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:46:04 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 11:52:09 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

extern void		check_operands_syntax_and_type(t_synt_tree *t, t_data *d)
{
	t->fmt[0] = 0;
	t->fmt[1] = 0;
	t->fmt[2] = 0;
	if (d->syntax == ATNT)
		check_atnt_syntax(t->child, d, t);
	else if (d->syntax == INTL)
		check_intel_syntax(t->child, d, t);
	else
		check_default_syntax(t->child, d, t);
}
