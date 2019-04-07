/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   param_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 11:34:31 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 14:58:57 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		param_size(unsigned char op, struct s_proc *p)
{
	int	s;

	s = 2;
	if (fparam(op) <= 1)
		s += fparam(op);
	else
		s += (fparam(op) == 2 && !i_inst(p->last_it)) ? 4 : 2;
	if (sparam(op) <= 1)
		s += sparam(op);
	else
		s += (sparam(op) == 2 && !i_inst(p->last_it)) ? 4 : 2;
	if (tparam(op) <= 1)
		s += tparam(op);
	else
		s += (tparam(op) == 2 && !i_inst(p->last_it)) ? 4 : 2;
	return (s);
}

int		get_param1(struct s_proc *p, struct s_vm *vm, unsigned char op, int pc)
{
	p->last_p1 = *((char *)vm->arena + pc);
	if (fparam(op) == 1)
		return (1);
	p->last_p1 <<= 8;
	p->last_p1 |= *((unsigned char *)vm->arena + ((pc + 1) % MEM_SIZE));
	if (fparam(op) == 3 || p->last_it == 10 || p->last_it == 14)
		return (2);
	p->last_p1 <<= 8;
	p->last_p1 |= *((unsigned char *)vm->arena + ((pc + 2) % MEM_SIZE));
	p->last_p1 <<= 8;
	p->last_p1 |= *((unsigned char *)vm->arena + ((pc + 3) % MEM_SIZE));
	return (4);
}

int		get_param2(struct s_proc *p, struct s_vm *vm, unsigned char op, int pc)
{
	p->last_p2 = *((char *)vm->arena + pc);
	if (sparam(op) == 1)
		return (1);
	p->last_p2 <<= 8;
	p->last_p2 |= *((unsigned char *)vm->arena + ((pc + 1) % MEM_SIZE));
	if (sparam(op) == 3 || p->last_it == 10 || p->last_it == 11 ||
			p->last_it == 14)
		return (2);
	p->last_p2 <<= 8;
	p->last_p2 |= *((unsigned char *)vm->arena + ((pc + 2) % MEM_SIZE));
	p->last_p2 <<= 8;
	p->last_p2 |= *((unsigned char *)vm->arena + ((pc + 3) % MEM_SIZE));
	return (4);
}

int		get_param3(struct s_proc *p, struct s_vm *vm, unsigned char op, int pc)
{
	p->last_p3 = *((char *)vm->arena + pc);
	if (tparam(op) == 1)
		return (1);
	p->last_p3 <<= 8;
	p->last_p3 |= *((unsigned char *)vm->arena + ((pc + 1) % MEM_SIZE));
	if (tparam(op) == 3 || p->last_it == 11)
		return (2);
	p->last_p3 <<= 8;
	p->last_p3 |= *((unsigned char *)vm->arena + ((pc + 2) % MEM_SIZE));
	p->last_p3 <<= 8;
	p->last_p3 |= *((unsigned char *)vm->arena + ((pc + 3) % MEM_SIZE));
	return (4);
}

void	get_params(struct s_proc *p, struct s_vm *vm, unsigned char op)
{
	int		pc;

	pc = (p->pcount + 2) % MEM_SIZE;
	pc += get_param1(p, vm, op, pc);
	pc %= MEM_SIZE;
	pc += get_param2(p, vm, op, pc);
	pc %= MEM_SIZE;
	get_param3(p, vm, op, pc);
}
