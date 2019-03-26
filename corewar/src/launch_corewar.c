/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_corewar.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 15:59:24 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 16:31:58 by shthevak    ###    #+. /#+    ###.fr     */
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

	load_champs(vm);
	create_processes(vm);
	init_params(vm);
	if (vm->flags & F_GRAPH)
	{
		vm->flags &= ~F_DUMP;
		cw_update_window(vm);
		sleep(4);
	}
/**************************/
	go_corewar(vm);
	i = 0;
	printf("\n\n");
	while (i < vm->players)
	{
		printf("\e[1m%s\e[0m: last live \e[33;1m%d\e[0m\n",
				vm->headers[i].prog_name, vm->llives[i]);
		i++;
	}
}
