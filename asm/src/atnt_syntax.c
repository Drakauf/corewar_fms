/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_syntax.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 18:55:24 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

int			set_ldi_sti(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	char	*s;
	int		type;
	int		j;
	t_pos	p;

	p = c->p;
	if (*c->s == '(')
		return (set_atnt_intel_addr_calc_syntax(c, d, t, i));
	if (t->type != LLDI_M)
		t->type = (i == 1) ? STI_M : LDI_M;
	s = c->s;
	if (*s == '*')
	{
		s++;
		if (!(j = is_label(s, d->label, d)))
		{
			if (*s == 'r' && ft_atoi(s + 1) > 0 && ft_atoi(s + 1) < REG_NUMBER
					&& (s[2] == ')' || s[3] == ')'))
			{
				p.col += 1;
				ft_perror(NULL, "indirect value can't be a register", &p, d);
				t->fmt[i] = -1;
				return (i);
			}
			if (ft_isalpha(*s))
			{
				t->fmt[i] = -1;
				p.col += s - c->s;
				ft_perror(NULL, "undefined label", &p, d);
				return (i);
			}
			if (!ft_isdigit(*s))
				return (i);
			while (ft_isdigit(*(++s)))
				;
		}
		else
			s += j;
		type = IND_O;
	}
	else
	{
		if (!(j = is_label(s, d->label, d)))
		{
			if (*s == '-')
				s++;
			if (!ft_isdigit(*s))
				return (i);
			while (ft_isdigit(*(++s)))
				;
		}
		else
			s += j;
		type = DIR_O;
	}
	if (*s != '(')
		return (i);
	t->fmt[i++] = type;
	s++;
	//operand 2 (T_DIR | T_REG)
	if (*s == '*')
	{
		p.col = c->p.col + (s - c->s);
		ft_perror(NULL, "argument 2 of addr can't be indirect", &p, d);
		t->fmt[i] = -1;
		return (i);
	}
	if (!(j = is_label(s, d->label, d)))
	{
		if (ft_isalpha(*s))
		{
			t->fmt[i] = -1;
			p.col += s - c->s;
			ft_perror(NULL, "undefined label", &p, d);
			return (i);
		}
		if (*s == '%' || *s == 'r')
		{
			s += (*s == '%') ? 2 : 1;
			if ((j = atoi(s)) < 1 || j > REG_NUMBER)
				return (i);
			while (ft_isdigit(*s))
				s++;
			type = REG_O;
		}
		else
		{
			if (*s == '-')
				s++;
			if (!ft_isdigit(*s))
				return (i);
			while (ft_isdigit(*(++s)))
				;
			type = DIR_O;
		}
	}
	else
	{
		s += j;
		type = DIR_O;
	}
	if (*s == ')')
		t->fmt[i] = type;
	else
		t->fmt[i - 1] = 0;
	return (i);
}

static int		set_lldi(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	t->type = LLDI_M;
	return (set_ldi_sti(c, d, t, i));
}

void		check_atnt_syntax(t_child *c, t_data *d, t_synt_tree *t)
{
	int		i;

	i = 0;
	while (c)
	{
		if ((t->fmt[i] = atnt_is_indirect(c->s, d, c, c->p)) == 0
				&& (t->fmt[i] = atnt_is_direct(c->s, d, c, c->p)) == 0
				&& (t->fmt[i] = atnt_is_register(c->s, d, c, c->p)) == 0)
		{
			if (t->type == LD_M || t->type == ST_M)
				i = set_ldi_sti(c, d, t, i);
			else if (t->type == LLD_M || t->type == LLDI_M)
				i = set_lldi(c, d, t, i);
			else
			{
				t->fmt[i] = -1;
				ft_perror(t->s, "two arguments address forbidden", &c->p, d);
			}
		}
//		else if (t->fmt[i] < 0)
//			ft_puts("\e[0;33mnot mov addr\e[0m\n");
		if (i == 0 && t->type == LD_M && t->fmt[0] == REG_O)
			t->type = ST_M;
		if (i != 0 && t->type == LLD_M)
			t->type = LLDI_M;
		check_operand_type(c, d, t, i);
		c = c->next;
		i++;
	}
}
