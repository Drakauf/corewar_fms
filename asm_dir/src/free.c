/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 08:30:27 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 11:27:41 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern void		free_all(t_data *d, t_synt_tree *tree)
{
	t_label	**label;
	int		i;

	label = (t_label**)d->label->tab;
	i = 0;
	while (i < d->label->len)
	{
		free(label[i]->name);
		free(label[i]);
		i++;
	}
	free(label);
	free(d->label);
	free_tree(tree);
	free(d->output);
	free(d->file);
}

extern void		free_tree(t_synt_tree *t)
{
	t_synt_tree		*tofree;
	t_child			*c;
	t_child			*tofree2;

	while (t)
	{
		tofree = t;
		t = t->next;
		c = tofree->child;
		while (c)
		{
			tofree2 = c;
			c = c->next;
			free(tofree2->s);
			free(tofree2);
		}
		free(tofree->s);
		free(tofree);
	}
}
