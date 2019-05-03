/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_mov_operand.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 12:44:05 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 12:47:47 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		write_addr_operand(int i, t_synt_tree *t, t_child *c, t_data *d)
{
	char	*s;
	int		type;
	int		size;
	int		off;

	s = c->s;
	size = g_binsize[t->type].opsize[i][t->fmt[i] - 1];
	type = t->fmt[i];
	off = write_operand(size, type, c->s, d);
	if (ft_strchr(c->s, '+'))
	{
		c->s = ft_strchr(c->s, '+') + 1;
		if (*c->s == ' ')
			c->s++;
	}
	else if (d->syntax == ATNT)
		c->s = ft_strchr(c->s, '(') + 1;
	i++;
	size = g_binsize[t->type].opsize[i][t->fmt[i] - 1];
	type = t->fmt[i];
	off += write_operand(size, type, c->s, d);
	c->s = s;
	return (off);
}

extern int		write_mov_operands(t_synt_tree *t, t_child *c, t_data *d)
{
	int		length;

	if (t->type == STI)
	{
		length = write_operand(g_binsize[t->type].opsize[0][t->fmt[0] - 1],
									t->fmt[0], c->s, d);
		c = c->next;
		length += write_addr_operand(1, t, c, d);
	}
	else
	{
		length = write_addr_operand(0, t, c, d);
		c = c->next;
		length += write_operand(g_binsize[t->type].opsize[2][t->fmt[2] - 1],
									t->fmt[2], c->s, d);
	}
	return (length);
}
