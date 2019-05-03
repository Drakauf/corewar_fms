/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 16:00:13 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 21:50:30 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "vector_sys.h"
#include "vector.h"

void		vector_reduce(t_vector *this)
{
	(void)this;
}

void		*vector_free(t_vector *this)
{
	int				i;

	if (this->type == VECTOR_PTR)
	{
		i = 0;
		while (i < this->len)
		{
			free(((char**)this->tab)[i++]);
		}
	}
	free(this->tab);
	free(this);
	return (NULL);
}
