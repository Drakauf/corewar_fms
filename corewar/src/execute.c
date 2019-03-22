/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 13:33:50 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 11:44:46 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

#undef fprintf
#undef printf
#define printf(f, ...)
#define fprintf(x, f, ...)

unsigned char	fparam(unsigned char op)
{
	return ((op & 192U) >> 6);
}

unsigned char	sparam(unsigned char op)
{
	return ((op & 48U) >> 4);
}

unsigned char	tparam(unsigned char op)
{
	return ((op & 12U) >> 2);
}

unsigned char	uparam(unsigned char op)
{
	return (op & 3U);
}

int		invalid_reg(int regnum)
{
	return (regnum < 1 || regnum > REG_NUMBER);
}

int		i_inst(int c)
{
	return (c == 10 || c == 11 || c == 14);
}	

int		param_size(unsigned char op, struct s_proc *p)
{
	int	size;

	size = 2;
	if (fparam(op) <= 1)
		size += fparam(op);
	else
		size += (fparam(op) == 2 && p->last_it != 10 && p->last_it != 14) ? 4 : 2;
	if (sparam(op) <= 1)
		size += sparam(op);
	else
		size += (sparam(op) == 2 && p->last_it != 10 && p->last_it != 11 && p->last_it != 14) ? 4 : 2;
	if (tparam(op) <= 1)
		size += tparam(op);
	else
		size += (tparam(op) == 2 && p->last_it != 11) ? 4 : 2;
	return (size);
}

int		get_int(void *arena, int pc, int offset)
{
	unsigned int	result;

	pc = (pc + offset) % MEM_SIZE;
	if (pc < 0)
		pc += MEM_SIZE;
	result = *((unsigned char *)arena + pc);
	result <<= 8;
	result |= *((unsigned char *)arena + (pc + 1) % MEM_SIZE);
	result <<= 8;
	result |= *((unsigned char *)arena + (pc + 2) % MEM_SIZE);
	result <<= 8;
	result |= *((unsigned char *)arena + (pc + 3) % MEM_SIZE);
	return ((int)result);
}

void	set_int(struct s_vm *vm, int pc, int player, unsigned int value)
{
	void	*arena;
	void	*ainfo;

	arena = vm->arena;
	ainfo = vm->ainfo;
	pc %= MEM_SIZE;
	if (pc < 0)
		pc += MEM_SIZE;
	*((unsigned char *)arena + (pc + 3) % MEM_SIZE) = (unsigned char)(value & 255U);
	value >>= 8;
	*((unsigned char *)arena + (pc + 2) % MEM_SIZE) = (unsigned char)(value & 255U);
	value >>= 8;
	*((unsigned char *)arena + (pc + 1) % MEM_SIZE) = (unsigned char)(value & 255U);
	value >>= 8;
	*((unsigned char *)arena + pc) = (unsigned char)(value & 255U);
	if (vm->flags & F_GRAPH)
	{
		*((char *)ainfo + pc) = (char)(player + (MAX_PLAYERS + 1) * vm->data->frate);
		*((char *)ainfo + (pc + 1) % MEM_SIZE) = (char)(player + (MAX_PLAYERS + 1) * vm->data->frate);
		*((char *)ainfo + (pc + 2) % MEM_SIZE) = (char)(player + (MAX_PLAYERS + 1) * vm->data->frate);
		*((char *)ainfo + (pc + 3) % MEM_SIZE) = (char)(player + (MAX_PLAYERS + 1) * vm->data->frate);
	}
}

int		wrong_op(struct s_proc *p)
{
	p->last_it = 0;
	p->last_op = 0;
	p->last_p1 = 0;
	p->last_p2 = 0;
	p->last_p3 = 0;
	p->carry = 0;
	p->pcount = (p->pcount + 1) % MEM_SIZE;
	return (0);
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

int		exec_sumcalc(struct s_proc *p, struct s_vm *vm, unsigned char op)
{
	get_params(p, vm, op);
	p->cooldown = 10;
	return (1);
}

int		exec_bitcalc(struct s_proc *p, struct s_vm *vm, unsigned char op)
{
	get_params(p, vm, op);
	p->cooldown = 6;
	return (1);
}

int		do_aff(unsigned char c, struct s_proc *p, struct s_vm *vm)
{
	p->last_op = *((unsigned char *)vm->arena + ((p->pcount + 1) % MEM_SIZE));
	get_param1(p, vm, 64U, p->pcount + 2);
	p->cooldown = 6;
	return (1);
}

int		do_live_or_pc(unsigned char c, struct s_proc *p, struct s_vm *vm)
{
	if (c == 1)
		get_param1(p, vm, 128U, p->pcount + 1);
	else
		get_param1(p, vm, 192U, p->pcount + 1);
	if (c == 1)
		p->cooldown = 10;
	else if (c == 9)
		p->cooldown = 20;
	else if (c == 12)
		p->cooldown = 800;
	else
		p->cooldown = 1000;
	return (1);
}

int		do_operation(unsigned char c, struct s_proc *p, struct s_vm *vm)
{
	p->last_op = *((unsigned char *)vm->arena + ((p->pcount + 1) % MEM_SIZE));
	if (c == 4 || c == 5)
		return (exec_sumcalc(p, vm, p->last_op));
	return (exec_bitcalc(p, vm, p->last_op));
}

int		do_load(unsigned char c, struct s_proc *p, struct s_vm *vm)
{
	p->last_op = *((unsigned char *)vm->arena + ((p->pcount + 1) % MEM_SIZE));
	get_params(p, vm, p->last_op);
	if (c == 2 || c == 3)
		p->cooldown = 5;
	else if (c == 10 || c == 11)
		p->cooldown = 25;
	else if (c == 13)
		p->cooldown = 10;
	else
		p->cooldown = 50;
	return (1);
}

int		live(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	if (p->last_p1 > vm->players || p->last_p1 <= 0)
	{
		p->pcount = (p->pcount + 5) % MEM_SIZE;
		return (0);
	}
	vm->llives[p->last_p1 - 1] = vm->tcycles;
	vm->lives += 1;
	p->lives += 1;
	p->pcount = (p->pcount + 5) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->carry);
}

int		ld(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	if (!(fparam(p->last_op) & 2) || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 0 || invalid_reg(p->last_p2))
	{
		p->pcount = (p->pcount + param_size(p->last_op & 240U, p)) % MEM_SIZE;
		return (0);
	}
	if (fparam(p->last_op) == 2)
		p->regs[p->last_p2 - 1] = p->last_p1;
	else
		p->regs[p->last_p2 - 1] = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	p->pcount = (p->pcount + param_size(p->last_op & 240U, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p2 - 1] == 0);
}

int		st(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	if (fparam(p->last_op) != 1 || !(sparam(p->last_op) & 1) ||
		tparam(p->last_op) != 0 || invalid_reg(p->last_p1) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)))
	{
		p->pcount = (p->pcount + param_size(p->last_op & 240U, p)) % MEM_SIZE;
		return (0);
	}
	if (sparam(p->last_op) == 1)
		set_int(vm, p->pcount + (p->regs[p->last_p2 - 1] % IDX_MOD), p->number,
			p->regs[p->last_p1 - 1]);
	else
		set_int(vm, p->pcount + (p->last_p2 % IDX_MOD), p->number,
			p->regs[p->last_p1 - 1]);
	p->pcount = (p->pcount + param_size(p->last_op & 240U, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->carry);
}

int		add(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	if (fparam(p->last_op) != 1 || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 1 || invalid_reg(p->last_p1) ||
		invalid_reg(p->last_p2) || invalid_reg(p->last_p3))
	{
		p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
		return (0);
	}
	p->regs[p->last_p3 - 1] = p->regs[p->last_p2 - 1] + p->regs[p->last_p1 - 1];
	p->pcount = (p->pcount + 5) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		sub(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	if (fparam(p->last_op) != 1 || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 1 || invalid_reg(p->last_p1) ||
		invalid_reg(p->last_p2) || invalid_reg(p->last_p3))
	{
		p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
		return (0);
	}
	p->regs[p->last_p3 - 1] = p->regs[p->last_p2 - 1] - p->regs[p->last_p1 - 1];
	p->pcount = (p->pcount + 5) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		and(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	t_reg	result;

	if (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3))
	{
		p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
		return (0);
	}
	if (fparam(p->last_op) == 1)
		result = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		result = p->last_p1;
	else
		result = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		result &= p->regs[p->last_p2 - 1];
	else if (sparam(p->last_op) == 2)
		result &= p->last_p2;
	else
		result &= get_int(vm->arena, p->pcount, p->last_p2 % IDX_MOD);
	p->regs[p->last_p3 - 1] = result;
	p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		or(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	t_reg	result;

	if (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3))
	{
		p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
		return (0);
	}
	if (fparam(p->last_op) == 1)
		result = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		result = p->last_p1;
	else
		result = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		result |= p->regs[p->last_p2 - 1];
	else if (sparam(p->last_op) == 2)
		result |= p->last_p2;
	else
		result |= get_int(vm->arena, p->pcount, p->last_p2 % IDX_MOD);
	p->regs[p->last_p3 - 1] = result;
	p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		xor(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	t_reg	result;

	if (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3))
	{
		p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
		return (0);
	}
	if (fparam(p->last_op) == 1)
		result = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		result = p->last_p1;
	else
		result = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		result ^= p->regs[p->last_p2 - 1];
	else if (sparam(p->last_op) == 2)
		result ^= p->last_p2;
	else
		result ^= get_int(vm->arena, p->pcount, p->last_p2 % IDX_MOD);
	p->regs[p->last_p3 - 1] = result;
	p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		zjmp(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	p->last_p1 %= IDX_MOD;
	if (p->carry)
	{
		p->pcount = (p->pcount + p->last_p1) % MEM_SIZE;
		if (p->pcount < 0)
			p->pcount += MEM_SIZE;
	}
	else
		p->pcount = (p->pcount + 3) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->carry);
}

int		ldi(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	int	index;

	if (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		sparam(p->last_op) == 3 || tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3))
	{
		p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
		return (0);
	}
	if (fparam(p->last_op) == 1)
		index = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		index = p->last_p1;
	else
		index = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		index += p->regs[p->last_p2 - 1];
	else
		index += p->last_p2;
	p->regs[p->last_p3 - 1] = get_int(vm->arena, p->pcount, index % IDX_MOD);
	p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		sti(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	int	index;

	if (fparam(p->last_op) != 1 || sparam(p->last_op) == 0 ||
		tparam(p->last_op) == 0 || tparam(p->last_op) == 3 ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		(tparam(p->last_op) == 1 && invalid_reg(p->last_p3)) ||
		invalid_reg(p->last_p1))
	{
		p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
		return (0);
	}
	if (sparam(p->last_op) == 1)
		index = p->regs[p->last_p2 - 1];
	else if (sparam(p->last_op) == 2)
		index = p->last_p2;
	else
		index = get_int(vm->arena, p->pcount, p->last_p2 % IDX_MOD);
	if (tparam(p->last_op) == 1)
		index += p->regs[p->last_p3 - 1];
	else
		index += p->last_p3;
	set_int(vm, p->pcount + (index % IDX_MOD), p->number, p->regs[p->last_p1 - 1]);
	p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->carry);
}

int		cfork(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	p->last_p1 %= IDX_MOD;
	fork_process(vm, p, p->last_p1);
	p->pcount = (p->pcount + 3) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->carry);
}

int		lld(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	if (!(fparam(p->last_op) & 2) || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 0 || invalid_reg(p->last_p2))
	{
		p->pcount = (p->pcount + param_size(p->last_op & 240U, p)) % MEM_SIZE;
		return (0);
	}
	if (fparam(p->last_op) == 2)
		p->regs[p->last_p2 - 1] = p->last_p1;
	else
		p->regs[p->last_p2 - 1] = get_int(vm->arena, p->pcount, p->last_p1);
	p->pcount = (p->pcount + param_size(p->last_op & 240U, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p2 - 1] == 0);
}

int		lldi(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	int	index;

	if (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		sparam(p->last_op) == 3 || tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3))
	{
		p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
		return (0);
	}
	if (fparam(p->last_op) == 1)
		index = p->regs[p->last_p1 - 1];
	else if (fparam(p->last_op) == 2)
		index = p->last_p1;
	else
		index = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	if (sparam(p->last_op) == 1)
		index += p->regs[p->last_p2 - 1];
	else
		index += p->last_p2;
	p->regs[p->last_p3 - 1] = get_int(vm->arena, p->pcount, index);
	p->pcount = (p->pcount + param_size(p->last_op, p)) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->regs[p->last_p3 - 1] == 0);
}

int		lfork(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	fork_process(vm, p, p->last_p1);
	p->pcount = (p->pcount + 3) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (p->carry);
}

int		aff(struct s_vm *vm, struct s_proc *p)
{
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	char	c;

	if (invalid_reg(p->last_p1))
	{
		p->pcount = (p->pcount + 3) % MEM_SIZE;
		return (0);
	}
	c = (char)p->regs[p->last_p1 - 1];
	if (!(vm->flags & F_GRAPH))
		write(1, &c, 1);
	p->pcount = (p->pcount + 3) % MEM_SIZE;
	printf("func %s, line %u: \e[36;1m%p\e[0m\n", __func__, __LINE__, p);
	return (c == 0);
}

void	execute_last(struct s_proc *p, struct s_vm *vm)
{
	static const t_exec		opers[16] =
	{
		&live, &ld, &st, &add, &sub, &and, &or, &xor,
		&zjmp, &ldi, &sti, &cfork, &lld, &lldi, &lfork, &aff
	};

	p->carry = opers[p->last_it - 1](vm, p);
}

int		execute(struct s_proc *p, struct s_vm *vm)
{
	static const char	*inst_names[17] = {
		"nop", "live", "ld", "st", "add", "sub", "and", "or", "xor", "zjmp",
		"ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};
	unsigned char		c;

	if (--(p->cooldown) == 1)
	{
#undef fprintf
int fprintf(FILE *s, const char *fmt, ...);
		fprintf(stderr, "process \e[1m%s\e[0m (pointer %p)\n", vm->champs[p->number - 1], p);
		fprintf(stderr, "Executing \e[33;1m%s\e[0m[%x](\e[1m%d, %d, %d\e[0m) at cycle %d\n\n", inst_names[p->last_it],
			p->pcount, p->last_p1, p->last_p2, p->last_p3, vm->tcycles);
		execute_last(p, vm);
		return (1);
	}
	if (p->cooldown > 1)
		return (0);
	p->cooldown = 0;
	fprintf(stderr, "process \e[1m%s\e[0m (pc %d)\n", vm->champs[p->number - 1], p->pcount);
#undef fprintf
	c = *((unsigned char *)vm->arena + p->pcount);
	if (c > 16 || c == 0)
		return (wrong_op(p));
	p->last_it = c;
	if (c >= 4 && c <= 8)
		return (do_operation(c, p, vm));
	if (c == 1 || c == 9 || c == 12 || c == 15)
		return (do_live_or_pc(c, p, vm));
	if (c == 16)
		return (do_aff(c, p, vm));
	return (do_load(c, p, vm));
}
