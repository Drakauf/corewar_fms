/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   intel_syntax.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 19:14:14 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

t_child		*rotate_left_operands(t_synt_tree *t)
{
	t_child	*tmp;
	t_child	*i;

	if (t->total_operands == 1)
		return (t->child);
	tmp = t->child;
	t->child = tmp->next;
	tmp->next = NULL;
	i = t->child;
	while (i->next)
		i = i->next;
	i->next = tmp;
	return (t->child);
}

static int		set_lldi(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	t->type = LLDI_M;
	return (set_atnt_intel_addr_calc_syntax(c, d, t, i));
}

void		check_intel_syntax(t_child *c, t_data *d, t_synt_tree *t)
{
	int		i;

	c = rotate_left_operands(t); // 1, 2, 3 -> 2, 3, 1
	i = 0;
	while (c)
	{
		if ((t->fmt[i] = intel_is_direct(c->s, d, c, c->p)) == 0
				&& (t->fmt[i] = intel_is_indirect(c->s, d, c, c->p)) == 0
				&& (t->fmt[i] = intel_is_register(c->s, d, c, c->p)) == 0)
		{
			if (t->type == LD_M || t->type == ST_M)
				i = set_atnt_intel_addr_calc_syntax(c, d, t, i);
			else if (t->type == LLD_M)
				i = set_lldi(c, d, t, i);
			else
			{
				t->fmt[i] = -1;
				ft_perror(t->s, "two arguments address forbidden", &c->p, d);
			}
		}
		if (i == 0 && t->type == LD_M && t->fmt[0] == REG_O)
			t->type = ST_M;
		check_operand_type(c, d, t, i);
		c = c->next;
		i++;
	}
}
