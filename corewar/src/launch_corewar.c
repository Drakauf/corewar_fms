/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_corewar.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 15:59:24 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 11:26:30 by mhouppin    ###    #+. /#+    ###.fr     */
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
		vm->data->frate = 15;
		vm->data->gcycles = 10;
	}
}

void	launch_corewar(struct s_vm *vm)
{
	int		i;
	int		max;
	int		imax;

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
}
