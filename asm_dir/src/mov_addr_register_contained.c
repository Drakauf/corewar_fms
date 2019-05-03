/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mov_addr_register_contained.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 15:08:50 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 14:39:32 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int	error_register(t_data *d, t_pos *p, int reg)
{
	if (!reg)
		return (0);
	ft_perror(NULL, "inexistant register", p, d);
	return (-1);
}

static int	error_register_expected(char *s, t_child *c, t_data *d, t_pos *p)
{
	p->col += s - c->s - 1;
	ft_perror(NULL, "`%` token expect register", p, d);
	return (-1);
}

extern int	register_contained(char **ps, t_data *d, t_child *c, t_pos p)
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
			return (error_register_expected(s, c, d, &p));
	}
	else if (*s != 'r')
		return (0);
	n = ft_atoi(++s);
	while (ft_isdigit(*s))
		s++;
	if (n < 1 || n > REG_NUMBER)
		return (error_register(d, &p, reg));
	*ps = s;
	return (type);
}
