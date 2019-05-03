/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_checks.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 14:18:56 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 14:24:58 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		sti_fail(struct s_proc *p)
{
	return (fparam(p->last_op) != 1 || sparam(p->last_op) == 0 ||
		tparam(p->last_op) == 0 || tparam(p->last_op) == 3 ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		(tparam(p->last_op) == 1 && invalid_reg(p->last_p3)) ||
		invalid_reg(p->last_p1));
}

int		ldi_fail(struct s_proc *p)
{
	return (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		sparam(p->last_op) == 3 || tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3));
}

int		bitset_fail(struct s_proc *p)
{
	return (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
			tparam(p->last_op) != 1 || invalid_reg(p->last_p3) ||
			(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
			(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)));
}
