/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_operand_into_tree.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 11:35:23 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 11:44:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		empty_operand(char **s, t_data *d)
{
	if (**s == ',') 
	{
		ft_perror(d->current->s, "empty operand", &d->p, d);
		d->current->remainder--;
		d->current->total_operands = -1;
	}
	return (skip_operand_after_error(s));
}

static char		*too_many_operands(char *s, t_data *d)
{
	ft_perror(d->current->s, "too many operands", &d->p, d);
	d->current->total_operands = -1;
	return (skip_all_but('\n', s));
}

static int		syntax_operand_error(char **s, t_data *d)
{
	d->p.col += *s - d->start - 1;
	ft_perror(d->current->s, "syntax operand", &d->p, d);
	d->p.col -= *s - d->start - 1;
	d->current->remainder--;
	d->current->total_operands = -1;
	return (skip_operand_after_error(s));
}

static int		illegal_character(char **s, t_data *d)
{
	d->p.col += *s - d->start;
	ft_perror(d->current->s, "illegal character", &d->p, d);
	d->p.col -= *s - d->start;
	d->current->remainder--;
	d->current->total_operands = -1;
	return (skip_operand_after_error(s));
}

extern int		write_operand_into_tree(char **s, t_data *d)
{
	if (d->current->remainder == 0)
	{
		*s = too_many_operands(*s, d);
		return (FATAL_ERROR);
	}
	if ((*s - d->start) == 0)
	{
		if (empty_operand(s, d) == -1)
			return (FATAL_ERROR);
	}
	else if (!ft_isalnum((*s)[-1]) && (*s)[-1] != ')' && (*s)[-1] != ',')
	{
		if (syntax_operand_error(s, d) == -1)
			return (FATAL_ERROR);
	}
	else if (**s != ',' && **s != ' ' && **s != '\t'
			&& **s != '\0' && **s != '\n' && !is_comment(d, **s))
	{
		if (illegal_character(s, d) == -1)
			return (FATAL_ERROR);
	}
	else
		push_new_operand(*s, d);
	return (0);
}
