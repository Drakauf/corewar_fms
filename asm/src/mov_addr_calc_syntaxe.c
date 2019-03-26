/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mov_addr_calc_syntax.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 19:20:25 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

int		indirect_contained(char **ps, t_data *d, t_child *c, t_pos p)
{
	char	*s;
	int		i;
	int		type;
	int		base;

	type = IND_O;
	s = *ps + 1;
	p = c->p;
	if (!(i = is_label(s, d->label, d)))
	{
		if (*s == 'r' && ft_atoi(s + 1) > 0 && ft_atoi(s + 1) < REG_NUMBER
				&& ((d->syntax == ATNT && (s[2] == ')' || s[3] == ')'))
				|| (s[2] == ']' || s[3] == ']')))
		{
			p.col += 1;
			ft_perror(NULL, "indirect value can't be a register", &p, d);
			return (-1);
		}
		if (ft_isalpha(*s))
		{
			p.col += s - c->s;
			ft_perror(NULL, "undefined label", &p, d);
			return (type);
		}
		base = get_base(*s == '-' ? s + 1 : s, c, d, &type);
		if (*s == '-')
		{
			if (base == 16)
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "token `-` before hexadecimal value", &p, d);
				type = -1;
			}
			else if (base == 8)
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "token `-` before octal value", &p, d);
				type = -1;
			}
			s++;
		}
		if (base == 16)
			s += 2;
		else if (base == 10 && !ft_isdigit(*s))
		{
			p.col = c->p.col + (s - c->s);
			type = -1;
		}
		s = skip_numbers_base(s, base);
	}
	else
		s += i;
	*ps = s;
	return (type);
}

int		direct_contained(char **ps, t_data *d, t_child *c, t_pos p)
{
	char	*s;
	int		type;
	int		base;
	int		j;

	type = DIR_O;
	s = *ps;// + 1;
	if (!(j = is_label(s, d->label, d)))
	{
		if (ft_isalpha(*s))
		{
			p.col = c->p.col + (s - c->s);
			ft_perror(NULL, "undefined label", &p, d);
			return (-1);
		}
		base = get_base(*s == '-' ? s + 1 : s, c, d, &type);
		if (*s == '-')
		{
			if (base == 16)
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "token `-` before hexadecimal value", &p, d);
				type = -1;
			}
			else if (base == 8)
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "token `-` before octal value", &p, d);
				type = -1;
			}
			s++;
		}
		if (base == 16)
			s += 2;
		*ps = skip_numbers_base(s, base);
	}
	else
		*ps = s + j;
	return (type);
}

int		numeric_direct_contained(char **ps, t_data *d, t_child *c, t_pos p)
{
	char	*s;
	int		type;
	int		base;

	type = DIR_O;
	s = *ps;
	base = get_base(*s == '-' ? s + 1 : s, c, d, &type);
	if (*s == '-')
	{
		if (base == 16)
		{
			p.col = c->p.col + (s - c->s);
			ft_perror(NULL, "token `-` before hexadecimal value", &p, d);
			type = -1;
		}
		else if (base == 8)
		{
			p.col = c->p.col + (s - c->s);
			ft_perror(NULL, "token `-` before octal value", &p, d);
			type = -1;
		}
		s++;
	}
	if (base == 16)
		s += 2;
	*ps = skip_numbers_base(s, base);
	return (type);
}

int		register_contained(char **ps, t_data *d, t_child *c, t_pos p)
{
	char	*s;
	int		n;
	int		type;
	int		reg;

	type = REG_O;
	s = *ps;
	reg = 0;
	if (d->syntax == ATNT && *s == '%')
	{
		reg = 1;
		if (*(++s) != 'r')
		{
			p.col += s - c->s - 1;
			ft_perror(NULL, "`%` token expect register", &p, d);
			return (-1);
		}
	}
	else if (*s != 'r')
		return (0);
	n = ft_atoi(++s);
	while (ft_isdigit(*s))
		s++;
	if (n < 1 || n > REG_NUMBER)
	{
		if (!reg)
			return (0);
		ft_perror(NULL, "inexistant register", &p, d);
		type = -1;
	}
	*ps = s;
	return (type);
}

int		set_atnt_intel_addr_calc_syntax(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	const char		pc = (d->syntax == ATNT) ? ')' : ']';
	char			*s;
	t_pos			p;
	int				j;

	if (t->type != LLDI_M)
		t->type = (i == 1) ? STI_M : LDI_M;
	s = c->s + 1;
	p = c->p;
	if (*s == '*')
		t->fmt[i] = indirect_contained(&s, d, c, c->p);
	else
	{
		if (!(j = is_label(s, d->label, d)))
		{
			if ((t->fmt[i] = register_contained(&s, d, c, p)) == 0)
				t->fmt[i] = numeric_direct_contained(&s, d, c, p);
		}
		else
		{
			t->fmt[i] = DIR_O;
			s += j;
		}
	}
	if (t->fmt[i] < 1)
		return (i);
	if (*s == ' ')
		s++;
	if (*s != '+')
	{
		p.col = c->p.col + (s - c->s);
		ft_perror(NULL, "unexpected token", &p, d);
		return (i);
	}
	if (*(++s) == ' ')
		s++;
	i++;
	// operand 2
	if (*s == '*')
	{
		p.col = c->p.col + (s - c->s);
		ft_perror(NULL, "argument 2 of addr can't be indirect", &p, d);
		t->fmt[i] = -1;
		return (i);
	}
	if ((t->fmt[i] = register_contained(&s, d, c, p)) == 0)
		t->fmt[i] = direct_contained(&s, d, c, p);
	if (t->fmt[i] < 1)
		return (i);
	t->fmt[i] = (j > 0) ? j : t->fmt[i];
	if (*s != pc)
	{
		p.col = c->p.col + (s - c->s);
		ft_perror(NULL, "unexpected token", &p, d);
		t->fmt[i] = -1;
	}
	return (i);
}
