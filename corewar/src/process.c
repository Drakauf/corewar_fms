/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 09:40:35 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 16:42:18 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

struct s_proc	*fresh_process(struct s_vm *vm, int pn, int pc)
{
	struct s_proc	*p;

	if (!(p = (struct s_proc *)malloc(sizeof(struct s_proc))))
		exit((ft_printf("\e[31;1mError\e[0m: %s\n", strerror(ENOMEM)) & 1) | 1);
	ft_memset(p, '\0', sizeof(struct s_proc));
	p->regs[0] = pn + 1;
	p->pcount = pc;
	p->number = pn + 1;
	return (p);
}

void	fork_process(struct s_vm *vm, struct s_proc *proc, int param)
{
	struct s_proc	*pnew;

	if (!(pnew = (struct s_proc *)malloc(sizeof(struct s_proc))))
		exit((ft_printf("\e[31;1mError\e[0m: %s\n", strerror(ENOMEM)) & 1) | 1);
	ft_memcpy(pnew, proc, sizeof(struct s_proc));
	pnew->pcount = (pnew->pcount + param) % MEM_SIZE;
	if (pnew->pcount < 0)
		pnew->pcount += MEM_SIZE;
	pnew->lives = 0;
	pnew->cooldown = 1;
	pnew->next = vm->processes;
	vm->processes = pnew;
}

void	kill_process(struct s_proc **proc, struct s_proc **vm, struct s_proc *last)
{
	struct s_proc	*tmp;

	tmp = (*proc)->next;
	if (!last)
	{
		free(*proc);
		*proc = tmp;
		*vm = tmp;
		return ;
	}
	last->next = tmp;
	free(*proc);
	*proc = tmp;
}

void	create_processes(struct s_vm *vm)
{
	int				p;
	struct s_proc	*proc;

	p = vm->players - 1;
	vm->processes = fresh_process(vm, p, vm->aspace * p);
	proc = vm->processes;
	while (p > 0)
	{
		p--;
		proc->next = fresh_process(vm, p, vm->aspace * p);
		proc = proc->next;
	}
	fprintf(stdout, "\n");
}
