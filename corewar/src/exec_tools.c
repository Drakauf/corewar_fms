/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 13:23:12 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 14:52:59 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	set_pc(struct s_proc *p, struct s_vm *vm, int x)
{
	register int	i;

	if (vm->verbose & VPCMOV)
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", x, (unsigned int)p->pcount,
				(unsigned int)(p->pcount + x));
		i = 0;
		while (i < x)
		{
			ft_printf("%.2hhx ",
					*((unsigned char *)vm->arena + (p->pcount + i) % MEM_SIZE));
			i++;
		}
		ft_printf("\n");
	}
	p->pcount = (p->pcount + x) % MEM_SIZE;
}

int		invalid_reg(int regnum)
{
	return (regnum < 1 || regnum > REG_NUMBER);
}

int		i_inst(int c)
{
	return (c == 10 || c == 11 || c == 14);
}
