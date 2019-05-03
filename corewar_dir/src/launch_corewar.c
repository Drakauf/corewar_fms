/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_corewar.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 15:59:24 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 17:31:58 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	init_params(struct s_vm *vm)
{
	vm->cycles = 0;
	vm->kcycles = CYCLE_TO_DIE;
	vm->tcycles = 0;
	vm->zcycles = CYCLE_TO_DIE;
	vm->lives = 0;
	vm->checks = 0;
	vm->mchecks = 10;
	if (vm->flags & F_GRAPH)
	{
		vm->data->frate = 25;
		vm->data->gcycles = 23;
	}
}

void	disp_results(struct s_vm *vm)
{
	int		i;
	int		max;
	int		idx_max;

	i = vm->players - 1;
	max = -1;
	idx_max = -1;
	while (i >= 0)
	{
		idx_max = (vm->llives[i] > max) ? i : idx_max;
		max = (vm->llives[i] > max) ? vm->llives[i] : max;
		i--;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", idx_max + 1,
		vm->headers[idx_max].prog_name);
	if (vm->flags & F_GRAPH)
	{
		cw_update_window(vm, vm->data, idx_max + 1);
		SDL_WaitEvent(&(vm->data->ev));
		while (vm->data->ev.type != SDL_QUIT &&
			vm->data->ev.type != SDL_KEYDOWN)
			SDL_WaitEvent(&(vm->data->ev));
	}
}

void	launch_corewar(struct s_vm *vm)
{
	SDL_Event	event;

	vm->next_pnum = 1;
	load_champs(vm);
	create_processes(vm);
	init_params(vm);
	if (vm->flags & F_GRAPH)
	{
		vm->flags &= ~F_DUMP;
		cw_update_window(vm, vm->data, 0);
		event.type = SDL_KEYDOWN;
		event.key.keysym.sym = SDLK_SPACE;
		SDL_PushEvent(&event);
		cw_update_window(vm, vm->data, 0);
	}
	go_corewar(vm);
	disp_results(vm);
}
