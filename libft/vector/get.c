/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 08:20:13 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/18 12:04:59 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "vector.h"

t_all	vector_get_index(t_vector *this, int i)
{
	if (this->type == VECTOR_INT)
		return ((t_all)(((int*)this->tab)[i]));
	if (this->type == VECTOR_PTR)
		return ((t_all)(((char**)this->tab)[i]));
	if (this->type == VECTOR_LONG)
		return ((t_all)(((long*)this->tab)[i]));
	if (this->type == VECTOR_DOUBLE)
		return ((t_all)(((double*)this->tab)[i]));
	if (this->type == VECTOR_SHORT)
		return ((t_all)(((short*)this->tab)[i]));
	if (this->type == VECTOR_FLOAT)
		return ((t_all)(((float*)this->tab)[i]));
	return ((t_all)(((char*)this->tab)[i]));
}
