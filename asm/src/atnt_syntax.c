/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_syntax.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 14:17:05 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

static int		set_ldi_sti(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	if (*c->s == '(')
		return (set_atnt_intel_addr_calc_syntax(c, d, t, i));
	return (set_atnt_alternative_addr_syntax(c, d, t, i));
}

static int		set_lldi(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	t->type = LLDI_M;
	return (set_ldi_sti(c, d, t, i));
}

static void		print_addr_syntax_forbidden(t_synt_tree *t, t_child *c, t_data *d, int i)
{
	t->fmt[i] = -1;
	ft_perror(t->s, "two arguments address forbidden", &c->p, d);
}

extern void		check_atnt_syntax(t_child *c, t_data *d, t_synt_tree *t)
{
	int		i;

	i = 0;
	while (c)
	{
		if ((t->fmt[i] = atnt_is_indirect(c->s, d, c, c->p)) == 0
				&& (t->fmt[i] = atnt_is_direct(c->s, d, c, c->p)) == 0
				&& (t->fmt[i] = atnt_is_register(c->s, d, c, c->p)) == 0)
		{
			if (t->type == LD_M || t->type == ST_M)
				i = set_ldi_sti(c, d, t, i);
			else if (t->type == LLD_M || t->type == LLDI_M)
				i = set_lldi(c, d, t, i);
			else
				print_addr_syntax_forbidden(t, c, d, i);
		}
		if (i == 0 && t->type == LD_M && t->fmt[0] == REG_O)
			t->type = ST_M;
		if (i != 0 && t->type == LLD_M)
			t->type = LLDI_M;
		check_operand_type(c, d, t, i);
		c = c->next;
		i++;
	}
}
