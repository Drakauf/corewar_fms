/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_calcs.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 13:58:47 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 15:39:24 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		add(struct s_vm *vm, struct s_proc *p)
{
	if (fparam(p->last_op) != 1 || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 1 || invalid_reg(p->last_p1) ||
		invalid_reg(p->last_p2) || invalid_reg(p->last_p3))
	{
		set_pc(p, vm, param_size(p->last_op, p));
		return (p->carry);
	}
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | add r%d r%d r%d\n", p->pnum, p->last_p1, p->last_p2,
			p->last_p3);
	p->regs[p->last_p3 - 1] = p->regs[p->last_p2 - 1] + p->regs[p->last_p1 - 1];
	set_pc(p, vm, 5);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		sub(struct s_vm *vm, struct s_proc *p)
{
	if (fparam(p->last_op) != 1 || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 1 || invalid_reg(p->last_p1) ||
		invalid_reg(p->last_p2) || invalid_reg(p->last_p3))
	{
		set_pc(p, vm, param_size(p->last_op, p));
		return (p->carry);
	}
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | sub r%d r%d r%d\n", p->pnum, p->last_p1, p->last_p2,
			p->last_p3);
	p->regs[p->last_p3 - 1] = p->regs[p->last_p1 - 1] - p->regs[p->last_p2 - 1];
	set_pc(p, vm, 5);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		and(struct s_vm *vm, struct s_proc *p)
{
	t_reg	result;
	t_reg	bitset;

	if (bitset_fail(p))
	{
		set_pc(p, vm, param_size(p->last_op, p));
		return (p->carry);
	}
	if (fparam(p->last_op) == 1)
		result = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		result = p->last_p1;
	else
		result = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		bitset = p->regs[p->last_p2 - 1];
	else if (sparam(p->last_op) == 2)
		bitset = p->last_p2;
	else
		bitset = get_int(vm->arena, p->pcount, p->last_p2 % IDX_MOD);
	(vm->verbose & VOPERS) ? ft_printf("P%5d | and %d %d r%d\n", p->pnum,
		result, bitset, p->last_p3) : 0;
	p->regs[p->last_p3 - 1] = result & bitset;
	set_pc(p, vm, param_size(p->last_op, p));
	return (p->regs[p->last_p3 - 1] == 0);
}

int		or(struct s_vm *vm, struct s_proc *p)
{
	t_reg	result;
	t_reg	bitset;

	if (bitset_fail(p))
	{
		set_pc(p, vm, param_size(p->last_op, p));
		return (p->carry);
	}
	if (fparam(p->last_op) == 1)
		result = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		result = p->last_p1;
	else
		result = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		bitset = p->regs[p->last_p2 - 1];
	else if (sparam(p->last_op) == 2)
		bitset = p->last_p2;
	else
		bitset = get_int(vm->arena, p->pcount, p->last_p2 % IDX_MOD);
	(vm->verbose & VOPERS) ? ft_printf("P%5d | or %d %d r%d\n", p->pnum,
		result, bitset, p->last_p3) : 0;
	p->regs[p->last_p3 - 1] = result | bitset;
	set_pc(p, vm, param_size(p->last_op, p));
	return (p->regs[p->last_p3 - 1] == 0);
}

int		xor(struct s_vm *vm, struct s_proc *p)
{
	t_reg	result;
	t_reg	bitset;

	if (bitset_fail(p))
	{
		set_pc(p, vm, param_size(p->last_op, p));
		return (p->carry);
	}
	if (fparam(p->last_op) == 1)
		result = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		result = p->last_p1;
	else
		result = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		bitset = p->regs[p->last_p2 - 1];
	else if (sparam(p->last_op) == 2)
		bitset = p->last_p2;
	else
		bitset = get_int(vm->arena, p->pcount, p->last_p2 % IDX_MOD);
	(vm->verbose & VOPERS) ? ft_printf("P%5d | xor %d %d r%d\n", p->pnum,
		result, bitset, p->last_p3) : 0;
	p->regs[p->last_p3 - 1] = result ^ bitset;
	set_pc(p, vm, param_size(p->last_op, p));
	return (p->regs[p->last_p3 - 1] == 0);
}
