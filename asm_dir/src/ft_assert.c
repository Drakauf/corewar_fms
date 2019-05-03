/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_assert.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 18:56:32 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 16:15:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

extern void		ft_assert(int cond, enum e_err err)
{
	static char	*fmt[] = {
		ERR "missing .name section\n",
		ERR "missing .comment section\n",
		ERR "cannot open file\n",
		ERR "Too few arguments\n",
		ERR "Too many arguments\n",
		ERR "invalid extension\n",
		ERR "can't create .cor file\n",
		ERR "no instructions\n",
		ERR "file name expected\n",
		ERR "output file name expected after -o\n",
		ERR "empty file\n",
		ERR "too large file (max = 0x7fffffff - 1)\n",
		ERR "lseek",
		ERR "too few memory available\n",
		ERR "read"
	};

	if (cond)
	{
		(err == LSEEK_ERROR || err == READ_ERROR) ?
			perror(fmt[err]) :
			write(2, fmt[err], ft_strlen(fmt[err]));
		exit(1);
	}
}
