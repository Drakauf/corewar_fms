/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_instruction.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:02:23 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 19:12:12 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		push_instruction(char **s, char *mnemonic, t_data *d, t_synt_tree **tree)
{
	int		opcode;

	opcode = get_opcode(mnemonic, d);
	if (opcode == -1)
	{
		ft_perror(mnemonic, "unknown mnemonic", &d->p, d);
		*s = skip_all_but('\n', *s);
		return (ERROR);
	}
	if (**s == '\0' || **s == '\n')
	{
		ft_perror(mnemonic, "too few operands", &d->p, d);
		return (ERROR);
	}
	if (d->current != NULL && d->current->type != LABEL_M)
	{
		ft_perror(d->current->s, "too many instructions", &d->current->p, d);
		*s = skip_all_but('\n', *s);
		return (ERROR);
	}
	d->current = push_new_instruction(tree, new_node(mnemonic, d, opcode));
	return (opcode);
}

extern char		*get_instruction(char *s, t_data *d, t_synt_tree **tree)
{
	char		*mnemonic;
	char		*start;

	start = s;
	while (is_not_space_or_label_end(*s, d))
		s++;
	mnemonic = ft_strndup(start, s - start);

	if (*s == ':')
		return (push_new_label(s + 1, mnemonic, d, tree));
	if (ft_strcmp(mnemonic, NAME_CMD_STRING) == 0)
		return (push_section_name_with_argument(s, mnemonic, d, tree));
	if (ft_strcmp(mnemonic, COMMENT_CMD_STRING) == 0)
		return (push_section_comment_with_argument(s, mnemonic, d, tree));
	if (*mnemonic == '.')
	{
		ft_perror(mnemonic, "imaginary section", &d->p, d);
		return (skip_all_but('\n', s));
	}
	if (push_instruction(&s, mnemonic, d, tree) == ERROR)
		return (s);
	d->p.col += s - start;
	return (get_operands(s, d));
}
