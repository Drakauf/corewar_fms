/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 12:07:03 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 13:53:01 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	next_player(struct s_vm *vm, char *player)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->champs[i] == NULL)
		{
			vm->champs[i] = player;
			return ;
		}
		i++;
	}
	exit((ft_printf("\e[31;1mError\e[0m: too much champs (max \e[1m%d\e[0m)\n",
		MAX_PLAYERS) & 1) | 1);
}

void	add_champ(struct s_vm *vm, char **argv, int i)
{
	int		a;

	if (!argv[i + 1])
		exit((ft_printf("\e[31;1mError\e[0m: missing number\n") & 1) | 1);
	if ((a = ft_atoi(argv[i + 1])) >= MAX_PLAYERS || a < 0)
		exit((ft_printf("\e[31;1mError\e[0m: -n number with "
			"\e[36;1m(0 <= number < %d)\e[0m\n", MAX_PLAYERS) & 1) | 1);
	if (!(argv[i + 2]))
		exit((ft_printf("\e[31;1mError\e[0m: missing champ name\n") & 1) | 1);
	if (vm->champs[a])
		exit((ft_printf("\e[31;1mError\e[0m: number %d already used by %s\n",
			a, vm->champs[a]) & 1) | 1);
	vm->champs[a] = argv[i + 2];
}

void	parse_argument(struct s_vm *vm, char **argv, int *ip)
{
	if (ft_strcmp(argv[*ip], "-dump") == 0)
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

int		main(int argc, char **argv)
{
	struct s_vm	vm;
	int			i;

	get_vmp()[0] = &vm;
	if (argc == 1 || !ft_strcmp(argv[1], "--help") || !ft_strcmp(argv[1], "-h"))
		exit_usage(argv[0]);
	ft_memset(&vm, '\0', sizeof(vm));
	i = 1;
	while (i < argc)
		parse_argument(&vm, argv, &i);
	if (!(vm.arena = malloc(MEM_SIZE)) || !(vm.ainfo = malloc(MEM_SIZE)))
		exit((ft_printf("\e[31;1mMalloc Error\e[0m\n") & 1) | 1);
	if (vm.flags & F_GRAPH)
	{
		vm.data = (struct s_vdata *)malloc(sizeof(struct s_vdata));
		cw_init_window(vm.data);
	}
	ft_memset(vm.arena, '\0', MEM_SIZE);
	ft_memset(vm.ainfo, '\0', MEM_SIZE);
	vm.players = get_champ_num(&vm);
	launch_corewar(&vm);
}
