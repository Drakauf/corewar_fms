/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 09:40:35 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 09:37:24 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

struct s_proc	*fresh_process(int pn, int pc, struct s_vm *vm)
{
	struct s_proc	*p;

	if (!(p = (struct s_proc *)malloc(sizeof(struct s_proc))))
		exit((ft_printf("\e[31;1mError\e[0m: %s\n", strerror(ENOMEM)) & 1) | 1);
	ft_memset(p, '\0', sizeof(struct s_proc));
	p->regs[0] = -(pn + 1);
	p->pcount = pc;
	p->pnum = vm->players + 1 - (vm->next_pnum++);
	p->number = pn + 1;
	return (p);
}

void			fork_process(struct s_vm *vm, struct s_proc *proc, int param)
{
	struct s_proc	*pnew;

	if (!(pnew = (struct s_proc *)malloc(sizeof(struct s_proc))))
		exit((ft_printf("\e[31;1mError\e[0m: %s\n", strerror(ENOMEM)) & 1) | 1);
	ft_memcpy(pnew, proc, sizeof(struct s_proc));
	pnew->pcount = (pnew->pcount + param) % MEM_SIZE;
	if (pnew->pcount < 0)
		pnew->pcount += MEM_SIZE;
	pnew->cooldown = 1;
	pnew->pnum = vm->next_pnum++;
	pnew->next = vm->forks;
	vm->forks = pnew;
}

void			kill_process(struct s_proc **proc, struct s_vm *vm,\
				struct s_proc *last)
{
	struct s_proc	*tmp;

	if (vm->verbose & VDEATHS)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			(*proc)->pnum, vm->tcycles - (*proc)->lives,
			vm->kcycles);
	tmp = (*proc)->next;
	if (!last)
	{
		free(*proc);
		*proc = tmp;
		vm->processes = tmp;
		return ;
	}
	last->next = tmp;
	free(*proc);
	*proc = tmp;
}

void			create_processes(struct s_vm *vm)
{
	int				p;
	struct s_proc	*proc;

	p = vm->players - 1;
	vm->processes = fresh_process(p, vm->aspace * p, vm);
	proc = vm->processes;
	while (p > 0)
	{
		p--;
		proc->next = fresh_process(p, vm->aspace * p, vm);
		proc = proc->next;
	}
}
