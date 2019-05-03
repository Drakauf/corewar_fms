/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 12:07:03 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 14:34:57 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		main(int argc, char **argv)
{
	struct s_vm	vm;
	int			i;

	get_vmp()[0] = &vm;
	ft_memset(&vm, '\0', sizeof(vm));
	if (argc == 1 || !ft_strcmp(argv[1], "--help") || !ft_strcmp(argv[1], "-h"))
		exit_usage(argv[0]);
	i = 1;
	while (i < argc)
		parse_argument(&vm, argv, &i);
	if (!(vm.arena = malloc(MEM_SIZE)))
		exit((ft_printf("\e[31;1mMalloc Error\e[0m\n") & 1) | 1);
	if (!(vm.ainfo = malloc(MEM_SIZE)))
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
	destroy(&vm);
	get_vmp()[0] = NULL;
}
