/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_alternative_addr_syntax.c                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 11:55:27 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 15:07:53 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		*indirect_value(char *s, t_data *d, t_child *c, int i)
{
	t_pos	p;
	int		j;

	p = c->p;
	if (!(j = is_label(++s, d->label, d)))
	{
		if (*s == 'r' && ft_atoi(s + 1) > 0 && ft_atoi(s + 1) < REG_NUMBER
				&& (s[2] == ')' || s[3] == ')'))
		{
			p.col += 1;
			return (perror_and_set_fmt("indirect value can't be a register", &p, d, d->current->fmt + i));
		}
		if (ft_isalpha(*s))
		{
			p.col += s - c->s;
			return (perror_and_set_fmt("undefined label", &p, d, d->current->fmt + i));
		}
		if (!ft_isdigit(*s))
			return (IND_ERROR);
		while (ft_isdigit(*(++s)))
			;
	}
	else
		s += j;
	return (s);
}

static char		*direct_value(char *s, t_data *d, t_child *c, int i)
{
	t_pos	p;
	int		j;

	p = c->p;
	if (!(j = is_label(s, d->label, d)))
	{
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
	}
	else
		s += j;
	return (s);
}

static char		*register_value(char *s, t_data *d, t_child *c, int i)
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

char	*get_arg_1(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	t_pos	p;
	char	*s;

	s = c->s;
	p = c->p;
	if (*s == '*')
	{
		if ((s = indirect_value(s, d, c, i)) == IND_ERROR)
			return (s);
		t->fmt[i] = IND_O;
	}
	else
	{
		if ((s = direct_value(s, d, c, i)) == DIR_ERROR)
			return (s);
		t->fmt[i] = DIR_O;
	}
	return (s);
}

char	*arg_2_indirect_error(char *s, t_child *c, t_data *d, int *fmt)
{
	t_pos	p;

	p.line = c->p.line;
	p.col = c->p.col + (s - c->s);
	perror_and_set_fmt("argument 2 of addr can't be indirect", &p, d, fmt);
	return (s);
}

char	*arg_2_undefined_error_label(char *s, t_child *c, t_data *d, int *fmt)
{
	t_pos	p;

	p.line = c->p.line;
	p.col = c->p.col + (s - c->s);
	perror_and_set_fmt("undefined label", &p, d, fmt);
	return (s);
}

char	*get_arg_2(char *s, t_child *c, t_data *d, int i)
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
			if ((s = register_value(s, d, c, i)) == REG_ERROR)
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

extern int		set_atnt_alternative_addr_syntax(t_child *c, t_data *d,
												t_synt_tree *t, int i)
{
	char	*s;
	t_pos	p;

	p.line = c->p.line;
	if (t->type != LLDI_M)
		t->type = (i == 1) ? STI_M : LDI_M;
	if ((s = get_arg_1(c, d, t, i)) == NULL)
		return (i);
	if (*s != '(')
	{
		p.col = c->p.col + (s - c->s);
		perror_and_set_fmt("missing token `(`", &p, d, t->fmt + i);
		return (i);
	}
	s++;
	i++;
	if ((s = get_arg_2(s, c, d, i)) == NULL)
		return (i);
	if (*s != ')')
	{
		p.col = c->p.col + (s - c->s);
		perror_and_set_fmt("missing token `)`", &p, d, t->fmt + i);
	}
	return (i);
}
