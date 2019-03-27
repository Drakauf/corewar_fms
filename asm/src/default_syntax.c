/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   default_syntax.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 18:56:02 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

void		check_default_syntax(t_child *c, t_data *d, t_synt_tree *t)
{
	int		i;

	i = 0;
	while (c)
	{
		if ((t->fmt[i] = dflt_is_direct(c->s, d, c, c->p)) == 0
				&& (t->fmt[i] = dflt_is_indirect(c->s, d, c, c->p)) == 0)
		{
			t->fmt[i] = dflt_is_register(c->s, d, c, c->p);
		}
		check_operand_type(c, d, t, i);
		c = c->next;
		i++;
	}
}
