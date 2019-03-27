/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   all_syntax_is_label.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 18:56:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** return(0) = eventuellement un autre type
** return(-1) = erreur deja affichee
** return (-2) = erreur non affichee
*/

int		atnt_is_direct(char *s, t_data *d, t_child *c, t_pos p)
{
	int		i;
	int		base;

	if (*s == '*' || *s == '(' || s[1] == '*')
		return (0);
	if (!(i = is_label(s, d->label, d)))
	{
		if (*s == '%')
			return (0);
		if (*s == 'r' && (ft_atoi(s + 1) < 1 || ft_atoi(s + 1) > REG_NUMBER))
		{
			ft_perror(NULL, "undefined label", &p, d);
			return (-1);
		}
		if (ft_isalpha(*s))
		{
			if (*s == 'r')
				return (0);
			ft_perror(NULL, "undefined label", &p, d);
			return (-1);
		}
		if (*s == '$')
			s++;
		base = get_base(*s == '-' ? s + 1 : s, c, d, &i);
		if (i == -1)
			return (-1);
		if (*s == '-')
		{
			if (base == 16)
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "token `-` before hexadecimal value", &p, d);
			ft_printf("return (-1) line %d\n", __LINE__);
				return (-1);
			}
			else if (base == 8)
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "token `-` before octal value", &p, d);
			ft_printf("return (-1) line %d\n", __LINE__);
				return (-1);
			}
			s++;
		}
		if (base == 16)
			s += 2;
		s = skip_numbers_base(s, base);
	}
	else
		s += i;
	if (*s == '(')
		return (0);
	return (*s != '\0' ? -2 : DIR_O);
}

int		atnt_is_indirect(char *s, t_data *d, t_child *c, t_pos p)
{
	int		i;
	int		base;

	if (*s != '(' || *s == '*' || s[1] == '%' || *(++s) == '*')
		return (0);
	if (!(i = is_label(s, d->label, d)))
	{
		if (*s == 'r' && ft_atoi(s + 1) > 0 && ft_atoi(s + 1) <= REG_NUMBER)
		{
			if (s[2] == ')' || s[3] == ')')
			{
				p.col += 1;
				ft_perror(NULL, "indirect value can't be a register", &p, d);
				return (-1);
			}
			return (0);
		}
		else if (ft_isalpha(*s))
		{
			p.col += 1;
			ft_perror(NULL, "undefined label", &p, d);
			return (-1);
		}
		base = get_base(*s == '-' ? s + 1 : s, c, d, &i);
		if (i == -1)
			return (-1);
		if (*s == '-')
		{
			if (base == 16)
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "token `-` before hexadecimal value", &p, d);
			ft_printf("return (-1) line %d\n", __LINE__);
				return (-1);
			}
			else if (base == 8)
			{
				p.col = c->p.col + (s - c->s);
				ft_perror(NULL, "token `-` before octal value", &p, d);
			ft_printf("return (-1) line %d\n", __LINE__);
				return (-1);
			}
			s++;
		}
		if (base == 16)
			s += 2;
		s = skip_numbers_base(s, base);
	}
	else
		s += i;
	if ((*s == ' ' && s[1] == '+') || *s == '+')
		return (0);
	return (*s == ')' && s[1] == '\0' ? IND_O : -2);
}

int		atnt_is_register(char *s, t_data *d, t_child *c, t_pos p)
{
	int		n;

	if (*s == '%')
	{
		if (*(++s) != 'r')
		{
			ft_perror(NULL, "`%` token expect register", &p, d);
			return (-1);
		}
	}
	else if (*s != 'r')
		return (0);
	s++;
	if (*s == '0')
	{
		ft_perror(NULL, "undefined label", &p, d);
		return (-1);
	}
	n = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (ft_isalpha(*s))
	{
		ft_perror(NULL, "undefined label", &p, d);
		return (-1);
	}
	if (n < 1 || n > REG_NUMBER)
	{
		ft_perror(NULL, "inexistant register", &p, d);
		return (-1);
	}
	return (*s != '\0' ? -2 : REG_O);
}
