/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mov_addr_check_arg2.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 15:06:41 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 12:05:45 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int	direct_contained(char **ps, t_data *d, t_child *c)
{
	char	*s;
	int		type;
	int		base;
	int		j;

	type = DIR_O;
	s = *ps;
	if (!(j = is_label(s, d->label, d)))
	{
		if ((s = is_undefined_label_or_register(s, d, c, c->p)) == NULL)
			return (-1);
		base = get_base(*s == '-' ? s + 1 : s, c, d, &type);
		if (type == -1 || (*s == '-' && print_error_base(&s, c, d, base) == -1))
			return (-1);
		if (base == 16)
			s += 2;
		if ((s = skip_numbers_base(s, base, c, d)) == NULL)
			return (-1);
		*ps = s;
	}
	else
		*ps = s + j;
	return (type);
}

extern void	check_mov_arg2(char *s, t_child *c, t_data *d, int *fmt)
{
	t_pos	p;

	p = c->p;
	if (*s == '*')
	{
		p.col = c->p.col + (s - c->s);
		ft_perror(NULL, "argument 2 of addr can't be indirect", &p, d);
		*fmt = -1;
		return ;
	}
	if ((*fmt = register_contained(&s, d, c, p)) == 0)
		*fmt = direct_contained(&s, d, c);
	if (*fmt < 1)
		return ;
	if ((d->syntax == ATNT && *s != ')') || (d->syntax == INTL && *s != ']'))
	{
		p.col = c->p.col + (s - c->s);
		ft_perror(NULL, "unexpected token", &p, d);
		*fmt = -1;
	}
}
