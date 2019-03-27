/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_operands.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:11:46 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 14:27:45 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		*skip_operand(char *s, t_data *d, char *start)
{
	while (1)
	{
		if (*s == ' ')
		{
			if (s[1] == '+')
				s++;
			else if	(s[-1] != '+')
				break ;
		}
		else if (is_comment(d, *s) || *s == ',' || *s == '\t'
				|| !is_authorized_char(d, *s))
			break ;
		else if (*s == ':')
		{
			if (d->syntax != DFLT
					|| ((s == start + 1 && s[-1] != '%') || s > start + 1))
			break ;
		}
		s++;
	}
	return (s);
}

static char		*too_many_operands(char *s, t_data *d)
{
	ft_perror(d->current->s, "too many operands", &d->p, d);
	return (skip_all_but('\n', s));
}

static int		syntax_operand_error(char **s, t_data *d, char *start)
{
	char	*nl;
	char	*comma;

	d->p.col += *s - start - 1;
	ft_perror(d->current->s, "syntax operand", &d->p, d);
	d->p.col -= *s - start - 1;
	if ((nl = ft_strchr(*s, '\n')) > (comma = ft_strchr(*s, ',')))
	{
		if (comma == NULL)
		{
			*s = nl;
			return (0);
		}
		*s = comma;
		return (0);
	}
	if (nl)
	{
		*s = nl;
		return (0);
	}
	*s = ft_strchr(*s, '\0');
	return (-1);
}

extern char		*get_operands(char *s, t_data *d)
{
	char	*start;
	char	*operand;

	while (1)
	{
		s = skip_spaces(s, &d->p);
		start = s;
		s = skip_operand(s, d, start);
		if (d->current->remainder == 0 && (s - start > 0))
			return (too_many_operands(s, d));
		if (!ft_isalnum(s[-1]) && s[-1] != ')' && s[-1] != ',')
		{
			if (syntax_operand_error(&s, d, start) == -1)
				return (s);
		}
		else if (*s != ',' && *s != ' ' && *s != '\t' && *s != '\0' && *s != '\n' && !is_comment(d, *s))
		{
			d->p.col += s - start;
			ft_perror(d->current->s, "illegal character", &d->p, d);
			d->p.col -= s - start;
			if (ft_strchr(s, '\n') > ft_strchr(s, ','))
			{
				if (ft_strchr(s, ',') == NULL)
					return (ft_strchr(s, '\0'));
				s = ft_strchr(s, ',');
			}
			else
				s = skip_all_but('\n', s);
			//return (skip_all_but('\n', s));
		}
		else if (s - start == 0)
		{
			if (*s == ',') //? ft_perror(d->current->s, "too few operands", &d->p, d) :
							ft_perror(d->current->s, "empty operand", &d->p, d);
			if (ft_strchr(s, '\n') > ft_strchr(s, ','))
			{
				if (ft_strchr(s, ',') == NULL)
					return (ft_strchr(s, '\0'));
				s = ft_strchr(s, ',');
			}
			else
				s = skip_all_but('\n', s);
		//	return (skip_all_but('\n', s));
		}
		operand = ft_strndup(start, s - start);
		push_new_child(d->current, new_child(operand, d));
		if (*s != ',' || *s == '\n')
			break ;
		d->p.col += (s - start) + 1;
		s++;
	}
	d->p.col += (s - start);
	if (d->current->remainder != 0)
	{
		ft_perror(d->current->s, "too few operands", &d->p, d);
		return (skip_all_but('\n', s));
	}
	check_operands_syntax_and_type(d->current, d);
	update_current_addr(d);
	return (skip_all_but('\n', s));
	//return (s);
}
