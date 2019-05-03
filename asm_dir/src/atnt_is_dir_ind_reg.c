/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   all_syntax_is_label.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 11:38:38 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** return(0) = eventuellement un autre type
** return(-1) = erreur deja affichee
** return (-2) = erreur non affichee
*/

static int		register_or_undefined_label(char *s, t_data *d, t_pos p)
{
	int		i;
	int		reg;

	reg = ((*s == '%' && s[1] == 'r' && ((!ft_isalnum(s[3]) && s[3] != '_')
				|| (!ft_isalnum(s[4]) && s[4] != '_')))
			|| (*s == 'r' && s[1] != '0' && ((!ft_isalnum(s[2]) && s[2] != '_')
				|| (!ft_isalnum(s[3]) && s[3] != '_'))));
	i = (*s == '%') ? ft_atoi(s + 2) : ft_atoi(s + 1);
	if (reg && (i < 1 || i > REG_NUMBER))
	{
		ft_perror(NULL, "inexistant register", &p, d);
		return (-1);
	}
	if (reg)
		return (0);
	if (ft_isalpha(*s) || *s == '_')
	{
		ft_perror(NULL, "undefined label", &p, d);
		return (-1);
	}
	return (1);
}

extern int		atnt_is_direct(char *s, t_data *d, t_child *c)
{
	int		i;
	int		base;

	if (*s == '*' || *s == '(' || s[1] == '*')
		return (0);
	if (!(i = is_label(s, d->label, d)))
	{
		if ((i = register_or_undefined_label(s, d, c->p)) != 1)
			return (i);
		if (*s == '$')
			s++;
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
	if (*s == '(')
		return (0);
	return (*s != '\0' ? -2 : DIR_O);
}

static int		register_or_undefined_label_2(char *s, t_data *d, t_pos p)
{
	int		i;

	if (*s == 'r' && s[1] != '0' && (i = ft_atoi(s + 1)) > 0 && i <= REG_NUMBER)
	{
		if (s[2] == ')' || s[3] == ')')
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

extern int		atnt_is_indirect(char *s, t_data *d, t_child *c)
{
	int		i;
	int		base;

	if (*s != '(' || *s == '*' || s[1] == '%' || *(++s) == '*')
		return (0);
	if (!(i = is_label(s, d->label, d)))
	{
		if ((i = register_or_undefined_label_2(s, d, c->p)) != 1)
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
	return (*s == ')' && s[1] == '\0' ? IND_O : -2);
}

extern int		atnt_is_register(char *s, t_data *d, t_child *c)
{
	int		n;

	if (*s == '%')
	{
		if (*(++s) != 'r' || s[1] == '0'
				|| (n = ft_atoi(s + 1)) < 1 || n > REG_NUMBER)
		{
			ft_perror(NULL, "`%` token expect register", &c->p, d);
			return (-1);
		}
	}
	else if (*s != 'r')
		return (0);
	s++;
	if (*s == '0')
		return (perror_undefined_label(d, c));
	n = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (ft_isalpha(*s))
		return (perror_undefined_label(d, c));
	if (n < 1 || n > REG_NUMBER)
		return (perror_inexistant_register(d, c));
	return (*s != '\0' ? -2 : REG_O);
}
