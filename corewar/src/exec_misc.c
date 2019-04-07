/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_misc.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 14:03:57 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 16:30:07 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		live(struct s_vm *vm, struct s_proc *p)
{
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | live %d\n", p->pnum, p->last_p1);
	p->lives = vm->tcycles;
	vm->lives += 1;
	if (p->last_p1 < -vm->players || p->last_p1 >= 0)
	{
		set_pc(p, vm, 5);
		return (p->carry);
	}
	vm->llives[-1 - p->last_p1] = vm->tcycles;
	if (vm->verbose & VLIVES)
		ft_printf("Player %d (%s) is said to be alive\n", -p->last_p1,
			vm->headers[-1 - p->last_p1].prog_name);
	set_pc(p, vm, 5);
	return (p->carry);
}

int		aff(struct s_vm *vm, struct s_proc *p)
{
	char	c;

	if (fparam(p->last_op) != 1 || invalid_reg(p->last_p1))
	{
		set_pc(p, vm, param_size(p->last_op & 192U, p));
		return (p->carry);
	}
	c = (char)p->regs[p->last_p1 - 1];
	if (!vm->verbose && !(vm->flags & F_GRAPH))
		write(1, &c, 1);
	set_pc(p, vm, 3);
	return (p->carry);
}

void	disp_sti(struct s_proc *p, int index, int idxsum)
{
	ft_printf("P%5d | sti r%d %d %d\n", p->pnum,
			p->last_p1, index, idxsum);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			index, idxsum, index + idxsum,
			p->pcount + (index + idxsum) % IDX_MOD);
}

void	disp_ldi(struct s_proc *p, int index, int idxsum)
{
	ft_printf("P%5d | ldi %d %d r%d\n", p->pnum,
			index, idxsum, p->last_p3);
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			index, idxsum, index + idxsum,
			p->pcount + (index + idxsum) % IDX_MOD);
}

void	disp_lldi(struct s_proc *p, int index, int idxsum)
{
	ft_printf("P%5d | lldi %d %d r%d\n", p->pnum,
			index, idxsum, p->last_p3);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			index, idxsum, index + idxsum,
			p->pcount + index + idxsum);
}
