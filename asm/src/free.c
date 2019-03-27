/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 08:30:27 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 12:25:57 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern void	free_data(t_data *d)
{
	d->label->free(d->label);
}

extern void	free_tree(t_synt_tree *t)
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
