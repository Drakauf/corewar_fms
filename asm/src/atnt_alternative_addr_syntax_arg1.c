/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_alternative_addr_syntax_arg1.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 15:22:47 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 15:23:16 by fcordon     ###    #+. /#+    ###.fr     */
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

extern char		*get_arg_1(t_child *c, t_data *d, t_synt_tree *t, int i)
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
