/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   load_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 09:13:43 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 12:06:16 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	reverse(unsigned int *a)
{
	unsigned int	swap;

	swap = ((*a >> 24) & 255) << 0;
	swap += ((*a >> 16) & 255) << 8;
	swap += ((*a >> 8) & 255) << 16;
	swap += ((*a >> 0) & 255) << 24;
	*a = swap;
}

void	read_champ(struct s_vm *vm, int p, int fd)
{
	int		i;

	read(fd, &(vm->headers[p].magic), 4);
	reverse(&(vm->headers[p].magic));
	if (vm->headers[p].magic != COREWAR_MAGIC)
		exit((ft_printf("\e[31;1mError\e[0m: invalid magic number\n") & 1) | 1);
	if (!(vm->headers[p].prog_name = (char *)malloc(PROG_NAME_LEN + 1)))
		exit((ft_printf("\e[31;1mError\e[0m: %s\n", strerror(ENOMEM)) & 1) | 1);
	if (!(vm->headers[p].comment = (char *)malloc(COMMENT_LEN + 1)))
		exit((ft_printf("\e[31;1mError\e[0m: %s\n", strerror(ENOMEM)) & 1) | 1);
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
	ft_printf("magic %u, comment %s, prog_size %u\n", vm->headers[p].magic, vm->headers[p].comment, vm->headers[p].prog_size);
	read(fd, &i, 4);
	i = 0;
	while (read(fd, vm->arena + vm->aspace * p + i, 1) == 1 && i < vm->headers[p].prog_size)
		i++;
	if (i != vm->headers[p].prog_size || read(fd, &i, 1))
		exit((ft_printf("\e[31;1mError\e[0m: champ size != header info (%d)\n", i) & 1) | 1);
	ft_memset(vm->ainfo + vm->aspace * p, p + 1, vm->headers[p].prog_size);
}

int		checksum(void *arena)
{
	int		i;
	int		r;

	i = 0;
	r = 0;
	while (i < MEM_SIZE)
	{
		r += *((char *)arena + i);
		i++;
	}
	return (r);
}

void	load_champs(struct s_vm *vm)
{
	int		p;
	int		fd;

	p = 0;
	vm->asize = MEM_SIZE;
	vm->aspace = vm->asize / vm->players;
	while (p < vm->players)
	{
		if ((fd = open(vm->champs[p], O_RDONLY)) == -1)
			exit((ft_printf("\e[31;1mError (file %s)\e[0m: %s\n", vm->champs[p],
							strerror(errno)) & 1) | 1);
		read_champ(vm, p, fd);
		ft_printf("Champ %s loaded successfully\n", vm->headers[p].prog_name);
		close(fd);
		p++;
	}
}
