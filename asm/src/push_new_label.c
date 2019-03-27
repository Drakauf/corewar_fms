/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   push_new_label.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:04:03 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 19:04:43 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

char	*push_new_label(char *s, char *label, t_data *d, t_synt_tree **tree)
{
	if (*label == '\0')
	{
		ft_perror(NULL, "label name expected before token `:`", &d->p, d);
		return (s);
	}
	if (!is_valid_label(label, d))
		ft_perror(NULL, "label syntax", &d->p, d);
	if (d->current && d->current->type == LABEL_M)
		ft_perror(NULL, "too many labels", &d->p, d);
	else if (d->current && d->current->type)
		ft_perror(NULL, "label must be before instruction", &d->p, d);
	if (duplicate_label(&label, d->label, d->cur_addr))
		ft_perror(NULL, "duplicate label", &d->p, d);
	else
		d->current = push_new_instruction(tree, new_node(label, d, 0));
	d->p.col += ft_strlen(label) + 1;
	return (s);
}
