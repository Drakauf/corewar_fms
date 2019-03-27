/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector_sys.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 16:08:50 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/02/25 16:09:04 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VECTOR_SYS_H
# define VECTOR_SYS_H

# include "vector.h"

void		vector_reduce(t_vector *this);
t_all		vector_delete(t_vector *usr_this, int index);
void		vector_insert(t_vector *usr_this, t_all val, int index);
void		vector_push_front(t_vector *usr_this, t_all val);
void		vector_push_back(t_vector *usr_this, t_all val);
t_all		vector_pop_front(t_vector *usr_this);
t_all		vector_pop_back(t_vector *this);
t_all		vector_get_index(t_vector *this, int i);
void		*vector_free(t_vector *this);

#endif
