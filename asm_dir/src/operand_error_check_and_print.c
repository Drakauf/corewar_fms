/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   operand_error_check_and_print.c                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 15:05:23 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 14:40:13 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern char		*is_undefined_label_or_register(char *s, t_data *d,
													t_child *c, t_pos p)
{
	register int	i;

	if (*s == 'r' && s[1] != '0' && (i = ft_atoi(s + 1)) > 0 && i <= REG_NUMBER
			&& ((d->syntax == ATNT && (s[2] == ')' || s[3] == ')'))
				|| (d->syntax == INTL && (s[2] == ']' || s[3] == ']'))))
	{
		p.col += 1;
		ft_perror(NULL, "indirect value can't be a register", &p, d);
		return (NULL);
	}
	if (ft_isalpha(*s))
	{
		p.col += s - c->s;
		ft_perror(NULL, "undefined label", &p, d);
		return (NULL);
	}
	return (s);
}

extern int		print_error_base(char **s, t_child *c, t_data *d, int base)
{
	t_pos	p;

	p.line = c->p.line;
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
	return (0);
}
