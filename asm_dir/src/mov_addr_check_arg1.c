/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mov_addr_check_arg1.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 15:06:27 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 12:35:43 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

/*
**		if ((s = is_undefined_label_or_register(s, d, c, c->p)) == NULL)
**			return (-1);
**		base = get_base(*s == '-' ? s + 1 : s, c, d, &i);
**		if (i == -1 || (*s == '-' && print_error_base(&s, c, d, base) == -1))
**			return (-1);
*/

static int		indirect_contained(char **ps, t_data *d, t_child *c)
{
	char	*s;
	int		i;
	int		base;

	s = *ps + 1;
	if (!(i = is_label(s, d->label, d)))
	{
		if ((s = is_undefined_label_or_register(s, d, c, c->p)) == NULL)
			return (-1);
		base = get_base(*s == '-' ? s + 1 : s, c, d, &i);
		if (i == -1 || (*s == '-' && print_error_base(&s, c, d, base) == -1))
			return (-1);
		if (base == 16)
			s += 2;
		else if (base == 10 && !ft_isdigit(*s))
			return (-1);
		if ((s = skip_numbers_base(s, base, c, d)) == NULL)
			return (-1);
	}
	else
		s += i;
	*ps = s;
	return (IND_O);
}

static int		check_negative_number(int base, char **s, t_data *d, t_child *c)
{
	t_pos	p;

	p = c->p;
	if (base == 16)
	{
		p.col = c->p.col + (*s - c->s);
		ft_perror(NULL, "token `-` before hexadecimal value", &p, d);
		return (-1);
	}
	else if (base == 8)
	{
		p.col = c->p.col + (*s - c->s);
		ft_perror(NULL, "token `-` before octal value", &p, d);
		return (-1);
	}
	(*s)++;
	return (DIR_O);
}

static int		numeric_direct_contained(char **s, t_data *d,
										t_child *c)
{
	int		type;
	int		base;
	char	*tmp;

	type = DIR_O;
	base = get_base(**s == '-' ? *s + 1 : *s, c, d, &type);
	if (**s == '-')
		type = check_negative_number(base, s, d, c);
	if (base == 16)
		*s += 2;
	if ((tmp = skip_numbers_base(*s, base, c, d)) == NULL)
		type = -1;
	*s = tmp;
	return (type);
}

static char		*error_plus(char *s, t_child *c, t_pos p, t_data *d)
{
	p.col = c->p.col + (s - c->s);
	ft_perror(NULL, "unexpected token", &p, d);
	return (NULL);
}

extern char		*check_mov_arg1(char *s, t_child *c, t_data *d, int *fmt)
{
	int	j;

	if (*s == '*')
		*fmt = indirect_contained(&s, d, c);
	else
	{
		if (!(j = is_label(s, d->label, d)))
		{
			if ((*fmt = register_contained(&s, d, c, c->p)) == 0)
				*fmt = numeric_direct_contained(&s, d, c);
		}
		else
		{
			*fmt = DIR_O;
			s += j;
		}
	}
	if (*fmt < 1)
		return (NULL);
	if (*s == ' ')
		s++;
	if (*s != '+')
		return (error_plus(s, c, c->p, d));
	s++;
	return ((*s == ' ') ? s + 1 : s);
}
