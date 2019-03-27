/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   champ_intro.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 10:59:59 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 11:08:33 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	champ_intro(struct s_vm *vm, int p, int fd)
{
	read(fd, &(vm->headers[p].magic), 4);
	reverse(&(vm->headers[p].magic));
	if (vm->headers[p].magic != COREWAR_MAGIC)
		exit((ft_printf("\e[31;1mError\e[0m: invalid magic number\n") & 1) | 1);
	if (!(vm->headers[p].prog_name = (char *)malloc(PROG_NAME_LEN + 1)))
		exit((ft_printf("\e[31;1mError\e[0m: %s\n", strerror(ENOMEM)) & 1) | 1);
	if (!(vm->headers[p].comment = (char *)malloc(COMMENT_LEN + 1)))
		exit((ft_printf("\e[31;1mError\e[0m: %s\n", strerror(ENOMEM)) & 1) | 1);
}
