/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_alternative_addr_syntax.c                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 11:55:27 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 12:09:43 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int		set_atnt_alternative_mov_addr_syntax(t_child *c, t_data *d,
												t_synt_tree *t, int i)
{
	char	*s;
	t_pos	p;

	p.line = c->p.line;
	if (t->type != LLDI)
		t->type = (i == 1) ? STI : LDI;
	if ((s = get_arg_1(c, d, t, i)) == NULL)
		return (i);
	if (*s != '(')
	{
		p.col = c->p.col + (s - c->s);
		perror_and_set_fmt("missing token `(`", &p, d, t->fmt + i);
		return (i);
	}
	s++;
	i++;
	if ((s = get_arg_2(s, c, d, i)) == NULL)
		return (i);
	if (*s != ')')
	{
		p.col = c->p.col + (s - c->s);
		perror_and_set_fmt("missing token `)`", &p, d, t->fmt + i);
	}
	return (i);
}
