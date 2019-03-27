/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_comment.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:09:48 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 19:40:23 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void		print_open_double_quote_error(char **s, t_data *d)
{
	if (**s == '\n' || **s == '\0')
		ft_perror(COMMENT_CMD_STRING, "missing operand", &d->p, d);
	else
	{
		ft_perror(COMMENT_CMD_STRING " operand", "syntax error", &d->p, d);
		*s = (skip_all_but('\n', *s));
	}
}

static void		print_close_double_quote_error(char *s, t_data *d, char *start)
{
	d->p.col += (s - start) + 1;
	if (s - start < PROG_COMMENT_LENGTH)
		ft_perror(COMMENT_CMD_STRING " operand", "unmatched token `\"`", &d->p, d);
	else
		ft_perror(COMMENT_CMD_STRING " operand", "to many characters", &d->p, d);
}

static char		*get_comment_and_check_error(char **s, t_data *d)
{
	char	*start;
	char	*comment;

	if (**s != '"')
	{
		print_open_double_quote_error(s, d);
		return (NULL);
	}
	start = ++(*s);
	while ((**s && **s != '\n' && (**s != '"' || (*s)[-1] == '\\'))
				&& (*s - start) < PROG_COMMENT_LENGTH)
	{
		(*s)++;
	}
	if (**s != '"')
	{
		print_close_double_quote_error(*s, d, start);
		return (NULL);
	}
	comment = ft_strndup(start, *s - start); //remplacer les '\"' par "
	d->p.col += (*s - start) + 1;
	return (comment);
}

extern char		*set_comment(char *s, t_data *d)
{
	s = skip_spaces(s, &d->p);
	if ((d->comment = get_comment_and_check_error(&s, d)) == NULL)
		return (s);
	d->current->child = new_child(d->comment, d);
	d->current->total_operands = 1;
	d->current->child->p = d->p;
	return (s + 1);
}