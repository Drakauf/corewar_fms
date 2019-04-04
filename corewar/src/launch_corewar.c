/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_corewar.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 15:59:24 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 15:42:14 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	init_params(struct s_vm *vm)
{
	vm->cycles = 0;
	vm->kcycles = CYCLE_TO_DIE;
	vm->tcycles = 0;
	vm->lives = 0;
	vm->checks = 0;
	vm->mchecks = 10;
	if (vm->flags & F_GRAPH)
	{
		vm->data->frate = 25;
		vm->data->gcycles = 17;
	}
}

void	launch_corewar(struct s_vm *vm)
{
	int		i;
	int		max;
	int		imax;

	vm->next_pnum = 1;
	load_champs(vm);
	create_processes(vm);
	init_params(vm);
	if (vm->flags & F_GRAPH)
	{
		vm->flags &= ~F_DUMP;
		cw_update_window(vm);
		sleep(4);
	}
	go_corewar(vm);
	i = 0;
	max = -1;
	imax = -1;
	while (i < vm->players)
	{
		imax = (vm->llives[i] > max) ? i : imax;
		max = (vm->llives[i] > max) ? vm->llives[i] : max;
		i++;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", imax + 1,
		vm->headers[imax].prog_name);
	if (vm->flags & F_GRAPH)
	{
		SDL_WaitEvent(&(vm->data->ev));
		while (vm->data->ev.type != SDL_QUIT && vm->data->ev.type != SDL_KEYDOWN)
			SDL_WaitEvent(&(vm->data->ev));
	}
}
