/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_assert.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 18:56:32 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 18:57:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern void		ft_assert(int cond, enum e_err err)
{
	static char	*fmt[] = {
		"\e[0;31mmissing .name section\e[0m\n",
		"\e[0;31mmissing .comment section\e[0m\n",
		"cannot open file\n",
		"Too few arguments\n",
		"Too many arguments\n",
		"invalid extension\n",
		"can't creat .cor file\n",
		"\e[0;31mno instructions\e[0m\n",
		"file name expected\n",
		"output file name expected after -o\n"
	};

	if (cond)
	{
		write(2, fmt[err], ft_strlen(fmt[err]));
		exit(-1);
	}
}
