/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 14:31:25 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/24 16:31:30 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	parse_argument(struct s_vm *vm, char **argv, int *ip)
{
	if (ft_strcmp(argv[*ip], "-dump") == 0 && argv[*ip + 1])
	{
		vm->flags |= F_DUMP;
		vm->dcycles = ft_atoi(argv[*ip + 1]);
		*ip += 2;
	}
	else if (ft_strcmp(argv[*ip], "-n") == 0)
	{
		add_champ(vm, argv, *ip);
		*ip += 3;
	}
	else if (ft_strcmp(argv[*ip], "-graphic") == 0)
	{
		vm->flags |= F_GRAPH;
		*ip += 1;
	}
	else if (ft_strcmp(argv[*ip], "-v") == 0 && argv[*ip + 1])
	{
		vm->flags |= F_VERB;
		vm->verbose = ft_atoi(argv[*ip + 1]);
		*ip += 2;
	}
	else
		next_player(vm, argv[(*ip)++]);
}

void	exit_usage(char *progname)
{
	ft_printf("%s [-dump ncycles] [-graphic] [[-n number] champ1.cor ...]\n",
			progname);
	ft_printf("\t-dump ncycles\t: dumps memory after ncycles executed\n");
	ft_printf("\t-graphic\t: toggles graphic view (SDL2)\n");
	ft_printf("\t-n number\t: specifies champ number, otherwise the next free "
			"is used\n");
	ft_printf("\t-v number\t: Verbosity levels, can be added together");
	ft_printf(" to enable several\n");
	ft_printf("\t\t\t - 0 : show only essentials\n");
	ft_printf("\t\t\t - 1 : show lives\n");
	ft_printf("\t\t\t - 2 : show cycles\n");
	ft_printf("\t\t\t - 4 : show operations\n");
	ft_printf("\t\t\t - 8 : show deaths\n");
	ft_printf("\t\t\t - 16 : show PC movements\n");
	ft_printf(" champ1.cor: champ source binary\n");
	exit(0);
}
