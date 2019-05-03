/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   load_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 13:33:24 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 13:44:57 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		get_int(void *arena, int pc, int offset)
{
	register unsigned int	result;

	pc = (pc + offset) % MEM_SIZE;
	if (pc < 0)
		pc += MEM_SIZE;
	result = *((unsigned char *)arena + pc);
	result <<= 8;
	result |= *((unsigned char *)arena + (pc + 1) % MEM_SIZE);
	result <<= 8;
	result |= *((unsigned char *)arena + (pc + 2) % MEM_SIZE);
	result <<= 8;
	result |= *((unsigned char *)arena + (pc + 3) % MEM_SIZE);
	return ((int)result);
}

void	set_int(struct s_vm *vm, int pc, int player, unsigned int value)
{
	void	*arena;
	void	*ainfo;

	arena = vm->arena;
	ainfo = vm->ainfo;
	pc = (pc % MEM_SIZE) + ((pc < 0) ? MEM_SIZE : 0);
	*((unsigned char *)arena + (pc + 3) % MEM_SIZE) = value & 255U;
	value >>= 8;
	*((unsigned char *)arena + (pc + 2) % MEM_SIZE) = value & 255U;
	value >>= 8;
	*((unsigned char *)arena + (pc + 1) % MEM_SIZE) = value & 255U;
	value >>= 8;
	*((unsigned char *)arena + pc) = value & 255U;
	if (vm->flags & F_GRAPH)
	{
		*((char *)ainfo + pc) =
			(char)(player + (MAX_PLAYERS + 1) * vm->data->frate);
		*((char *)ainfo + (pc + 1) % MEM_SIZE) =
			(char)(player + (MAX_PLAYERS + 1) * vm->data->frate);
		*((char *)ainfo + (pc + 2) % MEM_SIZE) =
			(char)(player + (MAX_PLAYERS + 1) * vm->data->frate);
		*((char *)ainfo + (pc + 3) % MEM_SIZE) =
			(char)(player + (MAX_PLAYERS + 1) * vm->data->frate);
	}
}
