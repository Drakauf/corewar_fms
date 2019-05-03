/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 13:33:50 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 14:18:29 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	execute_last(struct s_proc *p, struct s_vm *vm)
{
	static const t_exec		opers[16] = {
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
	unsigned char	c;

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
	{
		p->pcount = (p->pcount + 1) % MEM_SIZE;
		return (0);
	}
	p->last_it = c;
	if (c >= 4 && c <= 8)
		return (do_operation(c, p));
	if (c == 1 || c == 9 || c == 12 || c == 15)
		return (do_live_or_pc(c, p));
	if (c == 16)
		return (do_aff(c, p));
	return (do_load(c, p));
}
