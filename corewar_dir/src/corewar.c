/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 15:54:02 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 10:03:48 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		psize(struct s_proc *p)
{
	int		i;

	i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	return (i);
}

void	check_lives(struct s_vm *vm)
{
	struct s_proc	*proc;
	struct s_proc	*last;

	proc = vm->processes;
	last = NULL;
	while (proc)
	{
		if (vm->tcycles - proc->lives >= vm->kcycles)
			kill_process(&proc, vm, last);
		else
		{
			last = proc;
			proc = proc->next;
		}
	}
	if (!vm->processes)
		return ;
	if ((vm->lives >= NBR_LIVE) || ++vm->checks >= MAX_CHECKS)
	{
		vm->kcycles -= CYCLE_DELTA;
		if (vm->verbose & VCYCLES)
			ft_printf("Cycle to die is now %d\n", vm->kcycles);
		vm->checks = 0;
	}
	vm->zcycles = vm->tcycles + vm->kcycles;
}

void	dump_memory(struct s_vm *vm)
{
	unsigned char	c;
	int				i;

	i = 0;
	while (i < vm->asize)
	{
		if (!(i & 63))
			ft_printf("0x%.4x : ", (unsigned int)i);
		c = *((unsigned char *)vm->arena + i);
		ft_printf("%.2hhx ", c);
		i++;
		if (!(i & 63))
			ft_printf("\n");
	}
	exit(0);
}

void	update_info(struct s_vm *vm)
{
	struct s_proc	*tmp;

	if ((tmp = vm->forks) != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = vm->processes;
		vm->processes = vm->forks;
		vm->forks = NULL;
	}
	if (vm->tcycles >= vm->dcycles && (vm->flags & F_DUMP))
		dump_memory(vm);
	if (++vm->cycles >= vm->kcycles)
	{
		check_lives(vm);
		vm->lives = 0;
		vm->cycles = 0;
	}
	if ((vm->flags & F_GRAPH) && vm->tcycles % vm->data->gcycles == 0)
	{
		cw_update_window(vm, vm->data, 0);
		usleep(1000000 / vm->data->frate);
	}
}

void	go_corewar(struct s_vm *vm)
{
	struct s_proc	*p;

	while (vm->processes)
	{
		vm->tcycles++;
		if (vm->verbose & VCYCLES)
			ft_printf("It is now cycle %d\n", vm->tcycles);
		p = vm->processes;
		while (p)
		{
			execute(p, vm);
			p = p->next;
		}
		update_info(vm);
	}
}
