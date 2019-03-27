/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   push_section.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:06:11 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 19:06:35 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern char		*push_section_name_with_argument(char *s, char *section, t_data *d, t_synt_tree **tree)
{
	if (d->current)
	{
		ft_perror(d->current->s, "too many operands", &d->current->p, d);
		return (skip_all_but('\n', s));
	}
	if (d->header_stat & 0x1)
	{
		ft_perror(NAME_CMD_STRING, "duplicate section", &d->p, d);
		return (skip_all_but('\n', s));
	}
//	if (d->previous && d->previous->remainder)
//		ft_perror(d->previous->s, "too few operand", &d->p, d);
	d->header_stat |= 0x1;
	d->current = push_new_instruction(tree, new_node(section, d, SECTION_M));
	d->p.col += ft_strlen(section);
	return (set_name(s, d));
}

extern char		*push_section_comment_with_argument(char *s, char *section, t_data *d, t_synt_tree **tree)
{
	if (d->current)
	{
		ft_perror(d->current->s, "too many operands", &d->current->p, d);
		return (skip_all_but('\n', s));
	}
	if (d->header_stat & 0x2)
	{
		ft_perror(COMMENT_CMD_STRING, "duplicate section", &d->p, d);
		return (skip_all_but('\n', s));
	}
	d->header_stat |= 0x2;
	d->current = push_new_instruction(tree, new_node(section, d, SECTION_M));
	d->p.col += ft_strlen(section);
	return (set_comment(s, d));
}
