/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   push.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 15:18:42 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 16:26:36 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "vector.h"
#include "vector_sys.h"

static int	vector_new_alloc_after(t_vector *this)
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
	ft_memcpy(this->tab + this->elem, this->tab, this->elem * this->len);
	return (0);
}

static int	vector_new_alloc(t_vector *this)
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
	return (0);
}

void		vector_push_front(t_vector *this, t_all val)
{
	if (this->rem == 0)
	{
		if (vector_new_alloc_after(this) == -1)
			return ;
	}
	else
		ft_memmove(this->tab + this->elem, this->tab, this->len * this->elem);
	this->len++;
	this->rem--;
	if (this->type == VECTOR_INT)
		((int*)this->tab)[0] = (int)val;
	else if (this->type == VECTOR_PTR)
		((char**)this->tab)[0] = (char*)val;
	else if (this->type == VECTOR_LONG)
		((long*)this->tab)[0] = (long)val;
	else if (this->type == VECTOR_DOUBLE)
		((double*)this->tab)[0] = (double)val;
	else if (this->type == VECTOR_SHORT)
		((short*)this->tab)[0] = (short)val;
	else if (this->type == VECTOR_FLOAT)
		((float*)this->tab)[0] = (float)val;
	else
		this->tab[0] = (char)val;
}

void		vector_push_back(t_vector *this, t_all val)
{
	if (this->rem == 0)
	{
		if (vector_new_alloc(this) == -1)
			return ;
	}
	this->rem--;
	if (this->type == VECTOR_INT)
		((int*)this->tab)[this->len++] = (int)val;
	else if (this->type == VECTOR_PTR)
	{
		*((char**)(this->tab + (sizeof(char*) * this->len++))) = (char*)val;
	}
	else if (this->type == VECTOR_LONG)
		((long*)this->tab)[this->len++] = (long)val;
	else if (this->type == VECTOR_DOUBLE)
		((double*)this->tab)[this->len++] = (double)val;
	else if (this->type == VECTOR_SHORT)
		((short*)this->tab)[this->len++] = (short)val;
	else if (this->type == VECTOR_FLOAT)
		((float*)this->tab)[this->len++] = (float)val;
	else
		this->tab[this->len++] = (char)val;
}
