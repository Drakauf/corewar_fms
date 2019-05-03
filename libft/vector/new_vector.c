/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_vector.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 15:15:35 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 12:04:45 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "vector.h"
#include "vector_sys.h"

static int	get_size(int type)
{
	if (type == VECTOR_CHAR)
		return (1);
	else if (type == VECTOR_SHORT)
		return (sizeof(short));
	else if (type == VECTOR_INT)
		return (sizeof(int));
	else if (type == VECTOR_LONG)
		return (sizeof(long));
	else if (type == VECTOR_FLOAT)
		return (sizeof(float));
	else if (type == VECTOR_DOUBLE)
		return (sizeof(double));
	else
		return (sizeof(char*));
}

t_vector	*new_vector(int type, int blocksize)
{
	t_vector	*new;

	if (type > 6 || type < 0 || (new = malloc(sizeof(t_vector))) == NULL)
		return (NULL);
	new->push_back = &vector_push_back;
	new->push_front = &vector_push_front;
	new->pop_back = &vector_pop_back;
	new->pop_front = &vector_pop_front;
	new->insert = &vector_insert;
	new->delete = &vector_delete;
	new->free = &vector_free;
	new->reduce = &vector_reduce;
	new->get = &vector_get_index;
	new->len = 0;
	new->type = type;
	new->elem = get_size(type);
	new->blocksize = blocksize;
	new->rem = blocksize;
	new->tab = malloc(new->elem * blocksize);
	if (!new->tab)
	{
		free(new);
		return (NULL);
	}
	return (new);
}
