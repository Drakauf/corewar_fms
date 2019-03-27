/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   all_syntax_is_label.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 18:53:34 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

int		dflt_is_direct(char *s, t_data *d, t_child *c, t_pos p)
{
	int		i;
	int		base;

	if (*s != '%' || s[1] == '\0')
		return (0);
	s++;
	if (!(i = is_label(s, d->label, d)))
	{
		if (*s == 'r' && ft_atoi(s + 1) > 0 && ft_atoi(s + 1) <= REG_NUMBER)
		{
			ft_perror(NULL, "direct value can't be a register", &p, d);
			return (-1);
		}
		if (*s == ':' && s[1] != ':' && s[1] != '\0')
		{
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
	return (*s != '\0' ? -2 : DIR_O);
}

int		dflt_is_indirect(char *s, t_data *d, t_child *c, t_pos p)
{
	int		i;
	int		base;

	if (!(i = is_label(s, d->label, d)))
	{
		if (*s == 'r' && ft_atoi(s + 1) > 0 && ft_atoi(s + 1) <= REG_NUMBER)
			return (0);
		if (*s == ':' && s[1] != ':' && s[1] != '\0')
		{
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
	return (*s == '\0' ? IND_O : -2);
}

int		dflt_is_register(char *s, t_data *d, t_child *c, t_pos p)
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
		ft_perror(NULL, "inexistant register", &p, d);
		return (-1);
	}
	return (*s != '\0' ? -2 : REG_O);
}
