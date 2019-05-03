/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_instruction.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:02:23 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 17:03:38 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		push_instruction(char **s, char *mnemonic,
								t_data *d, t_synt_tree **tree)
{
	int		opcode;

	if ((opcode = get_opcode(mnemonic, d)) == -1)
	{
		ft_perror(NULL, "unknown mnemonic", &d->p, d);
		*s = skip_all_but('\n', *s);
		free(mnemonic);
		return (ERROR);
	}
	if (**s == '\0' || **s == '\n')
	{
		d->p.col += *s - d->start;
		ft_perror(mnemonic, "too few operands", &d->p, d);
		free(mnemonic);
		return (ERROR);
	}
	if (d->current != NULL && d->current->type != LABEL)
	{
		ft_perror(d->current->s, "too many instructions", &d->current->p, d);
		*s = skip_all_but('\n', *s);
		free(mnemonic);
		return (ERROR);
	}
	d->current = push_new_instruction(tree, new_node(mnemonic, d, opcode));
	return (opcode);
}

/*
** is_not_space_or_label_end() -> incremente s tant que le caractere est valide
**     et different de ':'.
**
** si mnemonic fini par ':' ou commence par '.', c'est un label ou une section.
**
** push_instruction() -> push l'instruction dans la liste chainee (tree)
**
** get_operand() -> recupere les operandes et les ajoute dans tree->child
*/

extern char		*get_instruction(char *s, t_data *d, t_synt_tree **tree)
{
	char		*mnemonic;

	d->start = s;
	while (is_not_space_or_label_end(*s))
		s++;
	mnemonic = ft_strndup(d->start, s - d->start);
	if (*s == ':')
		return (push_new_label(s + 1, mnemonic, d, tree));
	if (ft_strcmp(mnemonic, NAME_CMD_STRING) == 0)
		return (push_section_name_with_argument(s, mnemonic, d, tree));
	if (ft_strcmp(mnemonic, COMMENT_CMD_STRING) == 0)
		return (push_section_comment_with_argument(s, mnemonic, d, tree));
	if (*mnemonic == '.')
	{
		ft_perror(mnemonic, "unknown section", &d->p, d);
		free(mnemonic);
		return (skip_all_but('\n', s));
	}
	if (push_instruction(&s, mnemonic, d, tree) == ERROR)
		return (s);
	d->p.col += s - d->start;
	return (get_operands(s, d));
}
