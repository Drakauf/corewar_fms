/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_alternative_addr_syntax_arg2.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 15:19:07 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 15:22:06 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		*register_value_arg2(char *s, t_data *d, t_child *c, int i)
{
	t_pos	p;
	int		j;

	p = c->p;
	s += (*s == '%') ? 2 : 1;
	if ((j = ft_atoi(s)) < 1 || j > REG_NUMBER)
	{
		p.col += s - c->s;
		perror_and_set_fmt("undefined label", &p, d, d->current->fmt + i);
		return (REG_ERROR);
	}
	while (ft_isdigit(*s))
		s++;
	d->current->fmt[i] = REG_O;
	return (s);
}

static char		*direct_value_arg2(char *s, t_data *d, t_child *c, int i)
{
	t_pos	p;

	p = c->p;
	if (*s == '-')
		s++;
	if (!ft_isdigit(*s))
	{
		p.col += s - c->s;
		perror_and_set_fmt("unexpected token", &p, d, d->current->fmt + i);
		return (DIR_ERROR);
	}
	while (ft_isdigit(*(++s)))
		;
	d->current->fmt[i] = DIR_O;
	return (s);
}

static char		*arg_2_indirect_error(char *s, t_child *c, t_data *d, int *fmt)
{
	t_pos	p;

	p.line = c->p.line;
	p.col = c->p.col + (s - c->s);
	perror_and_set_fmt("argument 2 of addr can't be indirect", &p, d, fmt);
	return (s);
}

static char		*arg_2_undefined_error_label(char *s, t_child *c, t_data *d, int *fmt)
{
	t_pos	p;

	p.line = c->p.line;
	p.col = c->p.col + (s - c->s);
	perror_and_set_fmt("undefined label", &p, d, fmt);
	return (s);
}

extern char		*get_arg_2(char *s, t_child *c, t_data *d, int i)
{
	int			j;
	t_synt_tree	*t;

	t = d->current;
	if (*s == '*')
		return (arg_2_indirect_error(s, c, d, t->fmt + i));
	if (!(j = is_label(s, d->label, d)))
	{
		if (*s == '%' || *s == 'r')
		{
			if ((s = register_value_arg2(s, d, c, i)) == REG_ERROR)
				return (s);
		}
		else if (ft_isalpha(*s))
			return (arg_2_undefined_error_label(s, c, d, t->fmt + i));
		else if ((s = direct_value_arg2(s, d, c, i)) == DIR_ERROR)
			return (s);
	}
	else
	{
		s += j;
		t->fmt[i] = DIR_O;
	}
	return (s);
}
