/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_comment.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:09:48 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 15:46:47 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

#define ERR1	"missing operand"
#define ERR2	"syntax error"
#define ERR3	"unmatched token `\"`"
#define ERR4	"too many characters"

static void		print_open_double_quote_error(char **s, t_data *d)
{
	if (**s == '\n' || **s == '\0')
		ft_perror(COMMENT_CMD_STRING, ERR1, &d->p, d);
	else
	{
		ft_perror(COMMENT_CMD_STRING " operand", ERR2, &d->p, d);
		*s = (skip_all_but('\n', *s));
	}
}

static void		print_close_double_quote_error(char *s, t_data *d, char *start)
{
	d->p.col += (s - start) + 1;
	if (s - start < PROG_COMMENT_LENGTH)
		ft_perror(COMMENT_CMD_STRING " operand", ERR3, &d->p, d);
	else
		ft_perror(COMMENT_CMD_STRING " operand", ERR4, &d->p, d);
}

static int		set_back_slash(int *bckslsh)
{
	(*bckslsh)++;
	return (2);
}

static char		*get_comment_and_check_error(char **s, t_data *d)
{
	char	*start;
	int		n_bck_slash;

	if (**s != '"')
	{
		print_open_double_quote_error(s, d);
		return (NULL);
	}
	start = ++(*s);
	n_bck_slash = 0;
	while (**s && **s != '"' && (*s - start) - n_bck_slash < COMMENT_LENGTH)
	{
		if (**s == '\n')
			d->p.line++;
		(*s) += (**s == '\\') ? set_back_slash(&n_bck_slash) : 1;
	}
	if (**s != '"')
	{
		print_close_double_quote_error(*s, d, start);
		return (NULL);
	}
	return (escape_string(ft_strndup(start, *s - start), d));
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
