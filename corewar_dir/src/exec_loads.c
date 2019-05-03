/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_loads.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 13:54:18 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 16:45:57 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		ld(struct s_vm *vm, struct s_proc *p)
{
	if (!(fparam(p->last_op) & 2) || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 0 || invalid_reg(p->last_p2))
	{
		set_pc(p, vm, param_size(p->last_op & 240U, p));
		return (p->carry);
	}
	if (fparam(p->last_op) == 2)
		p->regs[p->last_p2 - 1] = p->last_p1;
	else
		p->regs[p->last_p2 - 1] = get_int(vm->arena, p->pcount,
				p->last_p1 % IDX_MOD);
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | ld %d r%d\n", p->pnum, p->regs[p->last_p2 - 1],
				p->last_p2);
	set_pc(p, vm, param_size(p->last_op & 240U, p));
	return (p->regs[p->last_p2 - 1] == 0);
}

int		lld(struct s_vm *vm, struct s_proc *p)
{
	if (!(fparam(p->last_op) & 2) || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 0 || invalid_reg(p->last_p2))
	{
		set_pc(p, vm, param_size(p->last_op & 240U, p));
		return (p->carry);
	}
	if (fparam(p->last_op) == 2)
		p->regs[p->last_p2 - 1] = p->last_p1;
	else
		p->regs[p->last_p2 - 1] =
			(short)get_int(vm->arena, p->pcount, p->last_p1);
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | lld %d r%d\n", p->pnum, p->regs[p->last_p2 - 1],
				p->last_p2);
	set_pc(p, vm, param_size(p->last_op & 240U, p));
	return (p->regs[p->last_p2 - 1] == 0);
}

int		ldi(struct s_vm *vm, struct s_proc *p)
{
	int	index;
	int	idxsum;

	if (ldi_fail(p))
	{
		set_pc(p, vm, param_size(p->last_op, p));
		return (p->carry);
	}
	if (fparam(p->last_op) == 1)
		index = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		index = p->last_p1;
	else
		index = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		idxsum = p->regs[p->last_p2 - 1];
	else
		idxsum = p->last_p2;
	if (vm->verbose & VOPERS)
		disp_ldi(p, index, idxsum);
	index += idxsum;
	p->regs[p->last_p3 - 1] = get_int(vm->arena, p->pcount, index % IDX_MOD);
	set_pc(p, vm, param_size(p->last_op, p));
	return (p->carry);
}

int		lldi(struct s_vm *vm, struct s_proc *p)
{
	int	index;
	int idxsum;

	if (ldi_fail(p))
	{
		set_pc(p, vm, param_size(p->last_op, p));
		return (p->carry);
	}
	if (fparam(p->last_op) == 1)
		index = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		index = p->last_p1;
	else
		index = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		idxsum = p->regs[p->last_p2 - 1];
	else
		idxsum = p->last_p2;
	if (vm->verbose & VOPERS)
		disp_lldi(p, index, idxsum);
	index += idxsum;
	p->regs[p->last_p3 - 1] = get_int(vm->arena, p->pcount, index);
	set_pc(p, vm, param_size(p->last_op, p));
	return (p->regs[p->last_p3 - 1] == 0);
}
