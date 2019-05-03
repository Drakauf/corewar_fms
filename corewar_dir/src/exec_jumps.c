/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_jumps.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 14:00:26 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 16:10:42 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		st(struct s_vm *vm, struct s_proc *p)
{
	if (fparam(p->last_op) != 1 || !(sparam(p->last_op) & 1) ||
		invalid_reg(p->last_p1) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)))
	{
		set_pc(p, vm, param_size(p->last_op & 240U, p));
		return (p->carry);
	}
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | st r%d %d\n", p->pnum, p->last_p1, p->last_p2);
	if (sparam(p->last_op) == 1)
		p->regs[p->last_p2 - 1] = p->regs[p->last_p1 - 1];
	else
		set_int(vm, p->pcount + (p->last_p2 % IDX_MOD), p->number,
			p->regs[p->last_p1 - 1]);
	set_pc(p, vm, param_size(p->last_op & 240U, p));
	return (p->carry);
}

int		sti(struct s_vm *vm, struct s_proc *p)
{
	int	index;
	int idxsum;

	if (sti_fail(p))
	{
		set_pc(p, vm, param_size(p->last_op, p));
		return (p->carry);
	}
	if (sparam(p->last_op) == 1)
		index = p->regs[p->last_p2 - 1];
	else if (sparam(p->last_op) == 2)
		index = p->last_p2;
	else
		index = get_int(vm->arena, p->pcount, p->last_p2 % IDX_MOD);
	if (tparam(p->last_op) == 1)
		idxsum = p->regs[p->last_p3 - 1];
	else
		idxsum = p->last_p3;
	if (vm->verbose & VOPERS)
		disp_sti(p, index, idxsum);
	index += idxsum;
	set_int(vm, p->pcount + (index % IDX_MOD), p->number,
			p->regs[p->last_p1 - 1]);
	set_pc(p, vm, param_size(p->last_op, p));
	return (p->carry);
}

int		zjmp(struct s_vm *vm, struct s_proc *p)
{
	if (p->carry)
	{
		p->pcount = (p->pcount + (p->last_p1 % IDX_MOD)) % MEM_SIZE;
		if (p->pcount < 0)
			p->pcount += MEM_SIZE;
		if (vm->verbose & VOPERS)
			ft_printf("P%5d | zjmp %d OK\n", p->pnum, p->last_p1);
	}
	else
	{
		if (vm->verbose & VOPERS)
			ft_printf("P%5d | zjmp %d FAILED\n", p->pnum, p->last_p1);
		set_pc(p, vm, 3);
	}
	return (p->carry);
}

int		cfork(struct s_vm *vm, struct s_proc *p)
{
	fork_process(vm, p, (p->last_p1 % IDX_MOD));
	if (vm->verbose & VOPERS)
	{
		ft_printf("P%5d | fork %d (%d)\n", p->pnum, p->last_p1,
			p->pcount + (p->last_p1 % IDX_MOD) % MEM_SIZE);
	}
	set_pc(p, vm, 3);
	return (p->carry);
}

int		lfork(struct s_vm *vm, struct s_proc *p)
{
	fork_process(vm, p, p->last_p1);
	if (vm->verbose & VOPERS)
	{
		ft_printf("P%5d | lfork %d (%d)\n", p->pnum, p->last_p1,
			p->pcount + p->last_p1);
	}
	set_pc(p, vm, 3);
	return (p->carry);
}
