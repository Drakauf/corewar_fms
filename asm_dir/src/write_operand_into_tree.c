/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_operand_into_tree.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 11:35:23 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 13:07:38 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void		empty_operand(t_data *d)
{
	ft_perror(d->current->s, "empty operand", &d->p, d);
	d->current->remainder--;
	d->current->total_operands = -1;
}

static char		*too_many_operands(char *s, t_data *d)
{
	ft_perror(d->current->s, "too many operands", &d->p, d);
	d->current->total_operands = -1;
	return (skip_all_but('\n', s));
}

static void		illegal_character(char **s, t_data *d)
{
	d->p.col += *s - d->start;
	ft_perror(NULL, "unexpected character", &d->p, d);
	d->p.col -= *s - d->start;
	d->current->remainder--;
	d->current->total_operands = -1;
	skip_operand_after_error(s);
}

extern int		write_operand_into_tree(char **s, t_data *d)
{
	if (d->current->remainder == 0)
	{
		*s = too_many_operands(*s, d);
		return (FATAL_ERROR);
	}
	if ((*s - d->start) == 0
			&& (**s == ',' || (**s == '\n' && (*s)[-1] == ',')))
		empty_operand(d);
	else if (**s != ',' && **s != '\n' && **s != '\t' && **s != ' '
				&& !is_comment(**s) && **s)
		illegal_character(s, d);
	else
		push_new_operand(*s, d);
	return (0);
}
