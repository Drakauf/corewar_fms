/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   load_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 09:13:43 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 13:52:23 by shthevak    ###    #+. /#+    ###.fr     */
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

int		get_champ_num(struct s_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!vm->champs[i])
		{
			if (i < MAX_PLAYERS - 1 && vm->champs[i + 1])
			{
				ft_printf("\e[31;1mError\e[0m: missing champ n.%d\n", i);
				exit(1);
			}
			break ;
		}
		i++;
	}
	if (!i)
		exit((ft_printf("\e[31;1mError\e[0m: no champs specified\n") & 1) | 1);
	return (i);
}

void	read_champ(struct s_vm *vm, int p, int fd)
{
	unsigned int		i;

	champ_intro(vm, p, fd);
	read(fd, vm->headers[p].prog_name, PROG_NAME_LEN);
	vm->headers[p].prog_name[PROG_NAME_LEN] = '\0';
	read(fd, &(vm->headers[p].prog_size), 4);
	read(fd, &(vm->headers[p].prog_size), 4);
	reverse(&(vm->headers[p].prog_size));
	if (vm->headers[p].prog_size > CHAMP_MAX_SIZE)
		exit((ft_printf("\e[31;1mError\e[0m: champ too heavy (%u bytes)\n",
						vm->headers[p].prog_size) & 1) | 1);
	if (!vm->headers[p].prog_size)
		ft_printf("\e[33;1mWarning\e[0m: empty champ (0 bytes)\n");
	read(fd, vm->headers[p].comment, COMMENT_LEN);
	read(fd, &i, 4);
	i = 0;
	while (read(fd, vm->arena + vm->aspace * p + i, 1) == 1
			&& i < vm->headers[p].prog_size)
		i++;
	if (i != vm->headers[p].prog_size || read(fd, &i, 1))
		exit((ft_printf("Error: champ size != header info(%d)\n", i) & 1) | 1);
	ft_memset(vm->ainfo + vm->aspace * p, p + 1, vm->headers[p].prog_size);
}

void	load_champs(struct s_vm *vm)
{
	int		p;
	int		fd;

	ft_printf("Introducing contestants...\n");
	p = 0;
	vm->asize = MEM_SIZE;
	vm->aspace = vm->asize / vm->players;
	while (p < vm->players)
	{
		if ((fd = open(vm->champs[p], O_RDONLY)) == -1)
			exit((ft_printf("\e[31;1mError (file %s)\e[0m: %s\n", vm->champs[p],
							strerror(errno)) & 1) | 1);
		read_champ(vm, p, fd);
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
			p + 1, vm->headers[p].prog_size, vm->headers[p].prog_name,
			vm->headers[p].comment);
		close(fd);
		p++;
	}
}
