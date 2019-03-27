/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 15:54:02 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 11:33:37 by shthevak    ###    #+. /#+    ###.fr     */
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

/*
** fprintf(stdout, "Checking process lives...\n");
** fprintf(stdout, "Decrementing vm->kcycles to \e[31;1m%d\e[0m\n",
** vm->kcycles);
** fprintf(stdout, "%s's process killed (pointer %p)\n",
** vm->champs[proc->number - 1], proc);
** fprintf(stdout, "\e[1m%d\e[0m processes still alive\n",
** psize(vm->processes));
*/

void	check_lives(struct s_vm *vm)
{
	struct s_proc	*proc;
	struct s_proc	*last;

	if ((vm->lives >= NBR_LIVE) || vm->checks == vm->mchecks)
	{
		vm->kcycles -= CYCLE_DELTA;
		vm->checks = 0;
	}
	proc = vm->processes;
	last = NULL;
	while (proc)
	{
		if (!proc->lives)
		{
			kill_process(&proc, &vm->processes, last);
		}
		else
		{
			proc->lives = 0;
			last = proc;
			proc = proc->next;
		}
	}
	vm->cycles = 0;
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
	if (++vm->tcycles >= vm->dcycles && (vm->flags & F_DUMP))
		dump_memory(vm);
	if (++vm->cycles == vm->kcycles)
		check_lives(vm);
	if ((vm->flags & F_GRAPH) && vm->tcycles % vm->data->gcycles == 0)
	{
		cw_update_window(vm);
		usleep(1000000 / vm->data->frate);
	}
}

/*
**		fprintf(stdout, "\e[35;1m - Cycle %d\e[0m\n\n", vm->tcycles);
*/

void	go_corewar(struct s_vm *vm)
{
	struct s_proc	*p;

	while (vm->processes)
	{
		p = vm->processes;
		while (p)
		{
			execute(p, vm);
			p = p->next;
		}
		update_info(vm);
	}
}
