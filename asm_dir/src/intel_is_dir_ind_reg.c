/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   intel_is_dir_ind_reg.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 18:14:42 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 15:41:36 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

static int		undefined_label_or_register(char *s, t_data *d, t_pos p)
{
	register int	i;

	if (*s == 'r' && s[1] != '0' && (i = ft_atoi(s + 1)) > 0 && i <= REG_NUMBER)
	{
		if (s[2] == ']' || s[3] == ']')
		{
			p.col += 1;
			ft_perror(NULL, "indirect value can't be a register", &p, d);
			return (-1);
		}
		return (0);
	}
	else if (ft_isalpha(*s) || *s == '_')
	{
		p.col += 1;
		ft_perror(NULL, "undefined label", &p, d);
		return (-1);
	}
	return (1);
}

extern int		intel_is_direct(char *s, t_data *d, t_child *c)
{
	int		i;
	int		base;

	if (*s == '[' || s[1] == '*')
		return (0);
	if (!(i = is_label(s, d->label, d)))
	{
		if (*s == 'r')
			return (0);
		base = get_base(*s == '-' ? s + 1 : s, c, d, &i);
		if (i == -1)
			return (-1);
		if (*s == '-' && print_error_base(&s, c, d, base) == -1)
			return (-1);
		if (base == 16)
			s += 2;
		if ((s = skip_numbers_base(s, base, c, d)) == NULL)
			return (-1);
	}
	else
		s += i;
	return (*s == '\0' ? DIR_O : -2);
}

extern int		intel_is_indirect(char *s, t_data *d, t_child *c)
{
	int		i;
	int		base;

	if (*s != '[' || *(++s) == '*')
		return (0);
	if (!(i = is_label(s, d->label, d)))
	{
		if ((i = undefined_label_or_register(s, d, c->p)) != 1)
			return (i);
		base = get_base(*s == '-' ? s + 1 : s, c, d, &i);
		if (i == -1 || (*s == '-' && print_error_base(&s, c, d, base) == -1))
			return (-1);
		if (base == 16)
			s += 2;
		if ((s = skip_numbers_base(s, base, c, d)) == NULL)
			return (-1);
	}
	else
		s += i;
	if ((*s == ' ' && s[1] == '+') || *s == '+')
		return (0);
	return ((*s == ']') ? IND_O : -2);
}

extern int		intel_is_register(char *s, t_data *d, t_child *c)
{
	int		n;

	(void)c;
	if (*s != 'r')
		return (0);
	s++;
	if (*s == '0')
	{
		ft_perror(NULL, "undefined label", &c->p, d);
		return (-1);
	}
	n = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (ft_isalpha(*s))
	{
		ft_perror(NULL, "undefined label", &c->p, d);
		return (-1);
	}
	if (n < 1 || n > REG_NUMBER)
	{
		ft_perror(NULL, "inexistant register", &c->p, d);
		return (-1);
	}
	return (*s != '\0' ? -2 : REG_O);
}
