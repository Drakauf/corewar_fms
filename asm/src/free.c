/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 08:30:27 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 17:49:43 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern void		free_all(t_data *d, t_synt_tree *tree)
{
	d->label->free(d->label);
	free_tree(tree);
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
