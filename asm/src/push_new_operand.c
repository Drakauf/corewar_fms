/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   push_new_operand.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 11:39:05 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 11:39:13 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern void	push_new_operand(char *s, t_data *d)
{
	char	*operand;

	operand = ft_strndup(d->start, s - d->start);
	push_new_child(d->current, new_child(operand, d));
}
