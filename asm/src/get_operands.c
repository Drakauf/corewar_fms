/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_operands.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:11:46 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 19:12:20 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern char		*get_operands(char *s, t_data *d)
{
	char	*start;
	char	*operand;

	while (1)
	{
		// Ameliorer check erreurs avant ?
		while (*s == ' ' || *s == '\t')
		{
			s++;
			d->p.col++;
		}
		start = s;
		while (1)
		{
			if (*s == ' ')
			{
				if (s[1] == '+')
					s++;
				else if	(s[-1] != '+')
					break ;
			}
			else if (is_comment(d, *s) || *s == ',' || *s == '\t' || !is_authorized_char(d, *s))
				break ;
			if (*s == ':' && d->syntax == DFLT && start != s)
				break ;
			s++;
		}
		if (d->current->remainder == 0)
		{
			ft_perror(d->current->s, "too many operands", &d->p, d);
			return (skip_all_but('\n', s));
		}
		if (!ft_isalnum(s[-1]) && s[-1] != ')' && s[-1] != ',')
		{
			d->p.col += s - start - 1;
			ft_perror(d->current->s, "syntax operand", &d->p, d);
			d->p.col -= s - start - 1;
			if (ft_strchr(s, '\n') > ft_strchr(s, ','))
			{
				if (ft_strchr(s, ',') == NULL)
					return (ft_strchr(s, '\0'));
				s = ft_strchr(s, ',');
			}
			else
				s = skip_all_but('\n', s);
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
