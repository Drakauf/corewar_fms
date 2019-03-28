/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_operands.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:11:46 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 11:43:05 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		*goto_operand_end(char *s, t_data *d)
{
	while (1)
	{
		if (*s == ' ')
		{
			if (s[1] == '+')
				s++;
			else if	(s[-1] != '+')
				break ;
		}
		else if (is_comment(d, *s) || *s == ',' || *s == '\t'
				|| !is_authorized_char(d, *s))
			break ;
		else if (*s == ':')
		{
			if (d->syntax != DFLT
					|| (
						(s == d->start + 1 && s[-1] != '%')
						|| s > d->start + 1
						)
				)
			break ;
		}
		s++;
	}
	return (s);
}

extern char		*get_operands(char *s, t_data *d)
{
	while (1)
	{
		s = skip_spaces(s, &d->p);
		d->start = s;
		s = goto_operand_end(s, d);
		if (write_operand_into_tree(&s, d) == FATAL_ERROR)
			return (s);
		if (*s != ',')
			break ;
		d->p.col += (s - d->start) + 1;
		s++;
	}
	d->p.col += (s - d->start);
	if (d->current->remainder > 0)
		ft_perror(d->current->s, "too few operands", &d->p, d);
	else if (d->current->total_operands > 0)
	{
		check_operands_syntax_and_type(d->current, d);
		update_current_addr(d);
	}
	return (skip_all_but('\n', s));
}
