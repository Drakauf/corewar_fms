/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_operand_type.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 15:31:31 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

extern void	check_operand_type(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	const t_inst_info		*info = &g_inst_info[t->type];
	int						cmp;

	cmp = t->fmt[i];
	if (cmp == 3)
		cmp = 4;
	if ((info->fmt[i] & cmp) == 0)
	{
		if (t->fmt[i] == REG_O)
			ft_perror(t->s, "incompatible type register", &c->p, d);
		else if (t->fmt[i] == IND_O)
			ft_perror(t->s, "incompatible type indirect", &c->p, d);
		else if (t->fmt[i] == DIR_O)
			ft_perror(t->s, "incompatible type direct", &c->p, d);
		else if (t->fmt[i] != -1)
			ft_perror(NULL, "syntax operand", &c->p, d);
	}
	else if (t->fmt[i] < -1)
		ft_perror(NULL, "syntax operand", &c->p, d);
}
