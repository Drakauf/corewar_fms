/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_check_operands.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 01:41:07 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 15:03:38 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

/*
** Hexa bloque par les fonction is_direct_value() && is_indirect_value()
** (le x de 0x ne passera pas)
**
** Les labels ne passent pas non plus (embetant pour un jump)
*/

extern int		altr_valid_label_syntax(const char *s)
{
	if (ft_isalpha(*s) || *s == '_')
	{
		while (ft_isalnum(*(++s)))
			;
		return (*s == '\0' ? 1 : 0);
	}
	return (0);
}

static void		check_syntax(t_data *d, t_synt_tree *tree)
{
	t_child	*c;
	int		i;
	
	while (tree)
	{
		if (tree->type == LABEL_M)
		{
			if (altr_valid_label_syntax(tree->s) == 0)
				ft_perror(NULL, "label syntax", &tree->p, d);
			tree = tree->next;
			continue ;
		}
		else if (tree->child)
		{
			c = tree->child;
			ft_memset(tree->fmt, '\0', 3 * sizeof(int));
			i = 0;
			while (c && i < tree->total_operands)
			{
				i = atnt_check_operand_type_syntax(d, c, tree, i);
				c = c->next;
			}
		}
		tree = tree->next;
	}
}

static void		update_operands_number(t_data *d, t_synt_tree *tree)
{
	int	i;

	while (tree)
	{
		if (tree->child)
		{
			i = 0;
			while (i < tree->total_operands)
			{
				if (tree->fmt[i] == 0 && tree->type != SECTION_M)
					ft_perror(NULL, "syntax operand", &tree->p, d);
				i++;
			}
		}
		if (tree->type)
			tree->total_operands = g_inst_info[tree->type].n_operand;
		tree = tree->next;
	}
}

extern void		check_operands_atnt(t_data *d, t_synt_tree *tree)
{
	check_syntax(d, tree);
	update_operands_number(d, tree);
	if (d->syntax_error)
		exit(-1);
	//uniformize_mov_instructions(d, tree); // sti, ldi, lldi.
}
