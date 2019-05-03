/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   struct_tree_and_child.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 18:58:41 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 11:28:40 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern t_child			*new_child(char *keyword, t_data *d)
{
	t_child	*new;

	new = malloc(sizeof(t_child));
	new->s = keyword;
	new->len = ft_strlen(new->s);
	new->p = d->p;
	new->next = NULL;
	return (new);
}

extern void				push_new_child(t_synt_tree *tree, t_child *new)
{
	t_child	*child;

	if (tree->child == NULL)
		tree->child = new;
	else
	{
		child = tree->child;
		while (child->next)
			child = child->next;
		child->next = new;
	}
	if (tree->remainder > 0)
	{
		tree->remainder--;
		tree->total_operands++;
	}
}

extern t_synt_tree		*new_node(char *s, t_data *d, int opcode)
{
	t_synt_tree	*new;

	new = malloc(sizeof(t_synt_tree));
	new->s = s;
	new->len = ft_strlen(s);
	new->p = d->p;
	new->total_operands = 0;
	new->remainder = (opcode > 0 && opcode < TOTAL_INST_NUMBER) ?
					g_inst_info[opcode].n_operand : 0;
	new->type = opcode;
	new->next = NULL;
	new->child = NULL;
	return (new);
}

extern t_synt_tree		*push_new_instruction(t_synt_tree **tree,
												t_synt_tree *new)
{
	t_synt_tree	*i;

	if (!*tree)
	{
		*tree = new;
		return (new);
	}
	i = *tree;
	while (i->next)
		i = i->next;
	i->next = new;
	return (new);
}
