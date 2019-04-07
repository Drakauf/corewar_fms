/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 13:33:50 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 11:48:43 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	set_pc(struct s_proc *p, struct s_vm *vm, int x)
{
	int				i;

	if (vm->verbose & VPCMOV)
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", x, (unsigned int)p->pcount,
			(unsigned int)(p->pcount + x));
		i = 0;
		while (i < x)
		{
			ft_printf("%.2hhx ",
				*((unsigned char *)vm->arena + (p->pcount + i) % MEM_SIZE));
			i++;
		}
		ft_printf("\n");
	}
	p->pcount = (p->pcount + x) % MEM_SIZE;
}

int		invalid_reg(int regnum)
{
	return (regnum < 1 || regnum > REG_NUMBER);
}

int		bitset_fail(struct s_proc *p)
{
	return (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3));
}

int		i_inst(int c)
{
	return (c == 10 || c == 11 || c == 14);
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
	p->pcount = (p->pcount + 1) % MEM_SIZE;
	return (0);
}

int		do_aff(unsigned char c, struct s_proc *p, struct s_vm *vm)
{
	p->cooldown = 2;
	return (1);
}

int		do_live_or_pc(unsigned char c, struct s_proc *p, struct s_vm *vm)
{
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
	if (c == 4 || c == 5)
		p->cooldown = 10;
	else
		p->cooldown = 6;
	return (1);
}

int		do_load(unsigned char c, struct s_proc *p, struct s_vm *vm)
{
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

int		ld(struct s_vm *vm, struct s_proc *p)
{
	if (!(fparam(p->last_op) & 2) || sparam(p->last_op) != 1 ||
		tparam(p->last_op) != 0 || invalid_reg(p->last_p2))
	{
		set_pc(p, vm, param_size(p->last_op & 240U, p));
		return (p->carry);
	}
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | ld %d r%d\n", p->pnum, p->last_p1, p->last_p2);
	if (fparam(p->last_op) == 2)
		p->regs[p->last_p2 - 1] = p->last_p1;
	else
		p->regs[p->last_p2 - 1] = get_int(vm->arena, p->pcount, p->last_p1 % IDX_MOD);
	set_pc(p, vm, param_size(p->last_op & 240U, p));
	return (p->regs[p->last_p2 - 1] == 0);
}

int		st(struct s_vm *vm, struct s_proc *p)
{
	if (fparam(p->last_op) != 1 || !(sparam(p->last_op) & 1) ||
		tparam(p->last_op) != 0 || invalid_reg(p->last_p1) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)))
	{
		set_pc(p, vm, param_size(p->last_op & 240U, p));
		return (p->carry);
	}
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | st r%d %d\n", p->pnum, p->last_p1, p->last_p2);
	if (sparam(p->last_op) == 1)
		set_int(vm, p->pcount + (p->regs[p->last_p2 - 1] % IDX_MOD), p->number,
			p->regs[p->last_p1 - 1]);
	else
		set_int(vm, p->pcount + (p->last_p2 % IDX_MOD), p->number,
			p->regs[p->last_p1 - 1]);
	set_pc(p, vm, param_size(p->last_op & 240U, p));
	return (p->carry);
}

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
	p->regs[p->last_p3 - 1] = p->regs[p->last_p2 - 1] - p->regs[p->last_p1 - 1];
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

int		ldi(struct s_vm *vm, struct s_proc *p)
{
	int	index;
	int	idxsum;

	if (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		sparam(p->last_op) == 3 || tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3))
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
	{
		ft_printf("P%5d | ldi %d %d r%d\n", p->pnum,
			index, idxsum, p->last_p3);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			index, idxsum, index + idxsum,
			(p->pcount + (index + idxsum) % IDX_MOD + MEM_SIZE) % MEM_SIZE);
	}
	index += idxsum;
	p->regs[p->last_p3 - 1] = get_int(vm->arena, p->pcount, index % IDX_MOD);
	set_pc(p, vm, param_size(p->last_op, p));
	return (p->regs[p->last_p3 - 1] == 0);
}

int		sti(struct s_vm *vm, struct s_proc *p)
{
	int	index;
	int idxsum;

	if (fparam(p->last_op) != 1 || sparam(p->last_op) == 0 ||
		tparam(p->last_op) == 0 || tparam(p->last_op) == 3 ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		(tparam(p->last_op) == 1 && invalid_reg(p->last_p3)) ||
		invalid_reg(p->last_p1))
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
	{
		ft_printf("P%5d | sti r%d %d %d\n", p->pnum,
			p->last_p1, index, idxsum);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			index, idxsum, index + idxsum,
			p->pcount + (index + idxsum) % IDX_MOD);
	}
	index += idxsum;
	set_int(vm, p->pcount + (index % IDX_MOD), p->number, p->regs[p->last_p1 - 1]);
	set_pc(p, vm, param_size(p->last_op, p));
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
		p->regs[p->last_p2 - 1] = get_int(vm->arena, p->pcount, p->last_p1);
	if (vm->verbose & VOPERS)
		ft_printf("P%5d | lld %d r%d\n", p->pnum, p->last_p1, p->last_p2);
	set_pc(p, vm, param_size(p->last_op & 240U, p));
	return (p->regs[p->last_p2 - 1] == 0);
}

int		lldi(struct s_vm *vm, struct s_proc *p)
{
	int	index;
	int idxsum;

	if (fparam(p->last_op) == 0 || sparam(p->last_op) == 0 ||
		sparam(p->last_op) == 3 || tparam(p->last_op) != 1 ||
		(fparam(p->last_op) == 1 && invalid_reg(p->last_p1)) ||
		(sparam(p->last_op) == 1 && invalid_reg(p->last_p2)) ||
		invalid_reg(p->last_p3))
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
	{
		ft_printf("P%5d | ldi %d %d r%d\n", p->pnum,
			index, idxsum, p->last_p3);
		ft_printf("       | -> long load from %d + %d = %d (with pc and mod %d)\n",
			index, idxsum, index + idxsum,
			(p->pcount + index + idxsum + MEM_SIZE) % MEM_SIZE);
	}
	index += idxsum;
	p->regs[p->last_p3 - 1] = get_int(vm->arena, p->pcount, index);
	set_pc(p, vm, param_size(p->last_op, p));
	return (p->regs[p->last_p3 - 1] == 0);
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

int		aff(struct s_vm *vm, struct s_proc *p)
{
	char	c;

	if (fparam(p->last_op) != 1 || invalid_reg(p->last_p1))
	{
		set_pc(p, vm, 2);
		return (p->carry);
	}
	c = (char)p->regs[p->last_p1 - 1];
	if (vm->verbose & VOPERS)
		ft_printf("Aff: %c\n", c);
	if (!(vm->flags & F_GRAPH))
		write(1, &c, 1);
	set_pc(p, vm, 3);
	return (c == 0);
}

void	execute_last(struct s_proc *p, struct s_vm *vm)
{
	static const t_exec		opers[16] =
	{
		&live, &ld, &st, &add, &sub, &and, &or, &xor,
		&zjmp, &ldi, &sti, &cfork, &lld, &lldi, &lfork, &aff
	};

	p->last_op = *((unsigned char *)vm->arena + (p->pcount + 1) % MEM_SIZE);
	if (p->last_it == 1)
		get_param1(p, vm, 128U, (p->pcount + 1) % MEM_SIZE);
	else if (p->last_it == 9 || p->last_it == 12 || p->last_it == 15)
		get_param1(p, vm, 192U, (p->pcount + 1) % MEM_SIZE);
	else if (p->last_it == 16)
		get_param1(p, vm, 64U, (p->pcount + 2) % MEM_SIZE);
	else
		get_params(p, vm, p->last_op);
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
		execute_last(p, vm);
		return (1);
	}
	if (p->cooldown > 1)
		return (0);
	p->cooldown = 0;
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
