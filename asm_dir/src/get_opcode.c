/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_opcode.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:13:57 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 12:06:42 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int			get_opcode(char *s, t_data *d)
{
	int		i;

	i = 1;
	while (i < TOTAL_INST_NUMBER)
	{
		if (ft_strcmp(s, d->inst_set[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}
