/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_insert.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 15:51:26 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 16:31:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "vector.h"
#include "vector_sys.h"

static int	vector_new_alloc_after_index(t_vector *this, int index)
{
	char	*new;

	new = ft_realloc(this->tab, this->elem * this->len,
			this->elem * (this->len + this->blocksize));
	if (!new)
	{
		free(this->tab);
		this->tab = NULL;
		this->len = 0;
		this->rem = 0;
		return (-1);
	}
	this->tab = new;
	this->rem += this->blocksize;
	ft_memcpy(this->tab, this->tab + index * this->elem,
			this->elem * (this->len - index));
	return (0);
}

t_all		vector_delete(t_vector *this, int index)
{
	t_all					ret;

	this->len--;
	this->rem++;
	if (this->type == VECTOR_INT)
		ret = (t_all)((int*)this->tab)[index];
	else if (this->type == VECTOR_PTR)
	{
		ret = 0;
		free(((char**)this->tab)[index]);
	}
	else if (this->type == VECTOR_LONG)
		ret = (t_all)((long*)this->tab)[index];
	else if (this->type == VECTOR_DOUBLE)
		ret = (t_all)((double*)this->tab)[index];
	else if (this->type == VECTOR_SHORT)
		ret = (t_all)((short*)this->tab)[index];
	else if (this->type == VECTOR_FLOAT)
		ret = (t_all)((float*)this->tab)[index];
	else
		ret = (t_all)this->tab[index];
	ft_memmove(this->tab + index * this->elem,
			this->tab + (index + 1) * this->elem, this->len * this->elem);
	return (ret);
}

void		vector_insert(t_vector *this, t_all val, int index)
{
	if (this->rem == 0)
	{
		if (vector_new_alloc_after_index(this, index) == -1)
			return ;
	}
	else
		ft_memmove(this->tab + (index + 1) * this->elem,
				this->tab + index * this->elem, this->len * this->elem);
	this->len++;
	this->rem--;
	if (this->type == VECTOR_INT)
		((int*)this->tab)[index] = (int)val;
	else if (this->type == VECTOR_PTR)
		((char**)this->tab)[index] = (char*)val;
	else if (this->type == VECTOR_LONG)
		((long*)this->tab)[index] = (long)val;
	else if (this->type == VECTOR_DOUBLE)
		((double*)this->tab)[index] = (double)val;
	else if (this->type == VECTOR_SHORT)
		((short*)this->tab)[index] = (short)val;
	else if (this->type == VECTOR_FLOAT)
		((float*)this->tab)[index] = (float)val;
	else
		this->tab[index] = (char)val;
}
