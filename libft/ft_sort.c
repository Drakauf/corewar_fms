/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_srtarray.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 14:12:19 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 12:46:56 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void				sort(void *a, void *a2, size_t elsiz, t_sortdata *x)
{
	size_t	o1;
	size_t	o2;
	void	*a1;
	size_t	cur;

	if ((a1 = ft_memdup(a, x->l1 * elsiz)) == NULL)
		return ;
	o1 = 0;
	o2 = 0;
	cur = 0;
	while (o1 < x->l1 || o2 < x->l2)
	{
		if (o1 >= x->l1)
			break ;
		else if (o2 >= x->l2)
			while (o1 < x->l1)
				ft_memcpy(a + (cur++ * elsiz), a1 + (o1++ * elsiz), elsiz);
		else if (x->cmp(a1 + (o1 * elsiz), a2 + (o2 * elsiz)) < 0)
			ft_memcpy(a + (cur * elsiz), a1 + (o1++ * elsiz), elsiz);
		else
			ft_memcpy(a + (cur * elsiz), a2 + (o2++ * elsiz), elsiz);
		cur++;
	}
	free(a1);
}

extern inline void		ft_sort(void *a1, size_t elemsiz,
					size_t len, int (*cmp)(void *a, void *b))
{
	t_sortdata	x;

	x.cmp = cmp;
	if (len > 3)
	{
		x.l1 = len / 2;
		x.l2 = len - x.l1;
		ft_sort(a1, elemsiz, x.l1, cmp);
		ft_sort((a1 + (x.l1 * elemsiz)), elemsiz, x.l2, cmp);
		sort(a1, (a1 + (x.l1 * elemsiz)), elemsiz, &x);
	}
	else if (len == 3)
	{
		x.l1 = 1;
		x.l2 = 2;
		ft_sort(a1 + elemsiz, elemsiz, x.l2, cmp);
		sort(a1, a1 + elemsiz, elemsiz, &x);
	}
	else if (len == 2)
	{
		x.l1 = 1;
		x.l2 = 1;
		sort(a1, a1 + elemsiz, elemsiz, &x);
	}
}
