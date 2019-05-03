/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_name.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:09:07 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 14:50:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		*print_open_double_quote_error(char **s, t_data *d)
{
	if (**s == '\n' || **s == '\0')
		ft_perror(NAME_CMD_STRING, "missing operand", &d->p, d);
	else
	{
		ft_perror(NAME_CMD_STRING " operand", "syntax error", &d->tmp_p, d);
		*s = (skip_all_but('\n', *s));
	}
	return (NULL);
}

static char		*print_close_double_quote_error(char *s, t_data *d, char *start)
{
	char	*line_start;

	line_start = s - (s[-1] == '\n') - 1;
	while (line_start >= start && *line_start != '\n')
		line_start--;
	d->p.col = (s - line_start);
	if (s - start < PROG_NAME_LENGTH)
		ft_perror(NAME_CMD_STRING " operand", "unmatched token `\"`", &d->p, d);
	else
		ft_perror(NAME_CMD_STRING " operand", "to many characters", &d->p, d);
	return (NULL);
}

static char		*name_length_error(char **s, t_data *d)
{
	ft_perror(NAME_CMD_STRING " operand", "empty string", &d->tmp_p, d);
	*s = skip_all_but('\n', *s);
	return (NULL);
}

static char		*get_name_and_check_error(char **s, t_data *d)
{
	char	*start;
	int		n_bck_slash;

	if (**s != '"')
		return (print_open_double_quote_error(s, d));
	start = ++(*s);
	n_bck_slash = 0;
	while (**s && **s != '"' && (*s - start) < NAME_LENGTH)
	{
		if (**s == '\n' && (*s)[1] != '\0')
			d->p.line++;
		else if (**s == '\\')
		{
			n_bck_slash++;
			(*s)++;
		}
		(*s)++;
	}
	if (**s != '"')
		return (print_close_double_quote_error(*s, d, start));
	if (*s - start == 0)
		return (name_length_error(s, d));
	return (escape_string(ft_strndup(start, *s - start), d));
}

extern char		*set_name(char *s, t_data *d)
{
	d->tmp_p = d->p;
	s = skip_spaces(s, &d->p);
	if ((d->name = get_name_and_check_error(&s, d)) == NULL)
		return (s);
	d->current->child = new_child(d->name, d);
	d->current->total_operands = 1;
	d->current->child->p = d->p;
	return (s + 1);
}
