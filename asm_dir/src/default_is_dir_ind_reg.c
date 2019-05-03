/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   all_syntax_is_label.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 15:25:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

static int		not_register_or_undefined_label(const char *s, t_data *d,
												t_pos p, int dir)
{
	register int	i;
	int				reg;
	const char		*end = s + 1;

	while (ft_isdigit(*end))
		end++;
	reg = (*s == 'r' && ft_isdigit(s[1]));
	if (reg && ((i = ft_atoi(s + 1)) < 1 || i > REG_N || s[1] == '0' || *end))
	{
		ft_perror(NULL, "inexistant register", &p, d);
		return (-1);
	}
	if (reg)
	{
		if (!dir)
			return (0);
		ft_perror(NULL, "direct value can't be a register", &p, d);
		return (-1);
	}
	if (*s == ':' && s[1] != ':' && s[1] != '\0')
	{
		ft_perror(NULL, "undefined label", &p, d);
		return (-1);
	}
	return (1);
}

extern int		dflt_is_direct(char *s, t_data *d, t_child *c)
{
	int		i;
	int		base;

	if (*s != '%')
		return (0);
	if (*(++s) == '\0')
		return (-2);
	if (!(i = is_label(s, d->label, d)))
	{
		if ((i = not_register_or_undefined_label(s, d, c->p, 1)) != 1)
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
	return (*s != '\0' ? -2 : DIR_O);
}

extern int		dflt_is_indirect(char *s, t_data *d, t_child *c)
{
	int		i;
	int		base;

	if (!(i = is_label(s, d->label, d)))
	{
		if ((i = not_register_or_undefined_label(s, d, c->p, 0)) != 1)
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
	return (*s == '\0' ? IND_O : -2);
}

extern int		dflt_is_register(char *s, t_data *d, t_child *c)
{
	int		n;

	if (*s != 'r')
		return (0);
	s++;
	if (*s == '0')
		return (-2);
	n = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (ft_isalpha(*s))
		return (-2);
	if (n < 1 || n > REG_NUMBER)
	{
		ft_perror(NULL, "inexistant register", &c->p, d);
		return (-1);
	}
	return (*s != '\0' ? -2 : REG_O);
}
