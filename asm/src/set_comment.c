/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_comment.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:09:48 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 19:10:05 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern char		*set_comment(char *s, t_data *d)
{
	char	*start;
	char	*comment;

	//d->current = push_new_instruction(tree, new_node(COMMENT_CMD_STRING, d, SECTION_M));
	while (*s == ' ' || *s == '\t')
	{
		d->p.col++;
		s++;
	}
	if (*s != '"')
	{
		if (*s == '\n' || *s == '\0')
		{
			ft_perror(COMMENT_CMD_STRING, "missing operand", &d->p, d);
			return (s);
		}
		ft_perror(COMMENT_CMD_STRING " operand", "syntax error", &d->p, d);
		return (skip_all_but('\n', s));
	}
	start = ++s;
	while ((*s && *s != '\n' && (*s != '"' || s[-1] == '\\')) && (s - start) < PROG_COMMENT_LENGTH)
		s++;
	if (*s != '"')
	{
		d->p.col += (s - start) + 1;
		if (s - start < PROG_COMMENT_LENGTH)
			ft_perror(COMMENT_CMD_STRING " operand", "unmatched token `\"`", &d->p, d);
		else
			ft_perror(COMMENT_CMD_STRING " operand", "to many characters", &d->p, d);
		return (s);
	}
	comment = ft_strndup(start, s - start);
	d->comment = comment;
	d->current->child = new_child(comment, d);
	d->current->total_operands = 1;
	d->current->child->p = d->p;
	d->p.col += (s - start) + 1;
	return (s + 1);
}
