/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pop.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 15:42:48 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/25 16:16:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "vector.h"
#include "vector_sys.h"

t_all		vector_pop_front(t_vector *this)
{
	t_all					ret;

	this->len--;
	this->rem++;
	if (this->type == VECTOR_INT)
		ret = (t_all)((int*)this->tab)[0];
	else if (this->type == VECTOR_PTR)
	{
		ret = 0;
		free(((char**)this->tab)[0]);
	}
	else if (this->type == VECTOR_LONG)
		ret = (t_all)((long*)this->tab)[0];
	else if (this->type == VECTOR_DOUBLE)
		ret = (t_all)((double*)this->tab)[0];
	else if (this->type == VECTOR_SHORT)
		ret = (t_all)((short*)this->tab)[0];
	else if (this->type == VECTOR_FLOAT)
		ret = (t_all)((float*)this->tab)[0];
	else
		ret = (t_all)this->tab[0];
	ft_memmove(this->tab, this->tab + this->elem, this->len * this->elem);
	return (ret);
}

t_all		vector_pop_back(t_vector *this)
{
	this->len--;
	this->rem++;
	if (this->type == VECTOR_INT)
		return (((int*)this->tab)[this->len]);
	else if (this->type == VECTOR_PTR)
	{
		free(((char**)this->tab)[this->len]);
		return (0);
	}
	else if (this->type == VECTOR_LONG)
		return (((long*)this->tab)[this->len]);
	else if (this->type == VECTOR_DOUBLE)
		return (((double*)this->tab)[this->len]);
	else if (this->type == VECTOR_SHORT)
		return (((short*)this->tab)[this->len]);
	else if (this->type == VECTOR_FLOAT)
		return (((float*)this->tab)[this->len]);
	else
		return (this->tab[this->len]);
}
