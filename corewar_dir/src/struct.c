/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   struct.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 14:41:31 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 11:57:40 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

struct s_vm	**get_vmp(void)
{
	static struct s_vm *vmp;

	return (&vmp);
}

void		destroy_vdata(struct s_vdata *data)
{
	int		i;

	SDL_DestroyTexture(data->tx);
	SDL_DestroyRenderer(data->rd);
	SDL_DestroyWindow(data->win);
	SDL_Quit();
	i = 0;
	if (data->font)
		while (i < 256)
		{
			free(data->font[i]);
			i++;
		}
	free(data->font);
	free(data);
}

void		destroy(struct s_vm *vm)
{
	struct s_proc	*pnext;
	int				i;

	free(vm->arena);
	free(vm->ainfo);
	if (vm->data)
		destroy_vdata(vm->data);
	while (vm->processes)
	{
		pnext = vm->processes->next;
		free(vm->processes);
		vm->processes = pnext;
	}
	i = 0;
	while (i < vm->players)
	{
		free(vm->headers[i].prog_name);
		free(vm->headers[i].comment);
		i++;
	}
}

void		destroy_vm(void)
{
	struct s_vm		*vm;

	vm = *get_vmp();
	if (!vm)
		return ;
	destroy(vm);
}
