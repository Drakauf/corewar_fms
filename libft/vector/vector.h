/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 16:09:19 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 08:24:11 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "../libft.h"

# define VECTOR_CHAR	0
# define VECTOR_UCHAR	0
# define VECTOR_SHORT	1
# define VECTOR_USHORT	1
# define VECTOR_INT		2
# define VECTOR_UINT	2
# define VECTOR_LONG	3
# define VECTOR_ULONG	3
# define VECTOR_FLOAT	4
# define VECTOR_DOUBLE	5
# define VECTOR_PTR		6

# undef tab

typedef long				t_all;
typedef struct s_vector		t_vector;

struct		s_vector
{
	void		(*push_back)(t_vector*, t_all);
	void		(*push_front)(t_vector*, t_all);
	void		(*insert)(t_vector*, t_all, int);
	t_all		(*delete)(t_vector*, int);
	t_all		(*pop_back)(t_vector*);
	t_all		(*pop_front)(t_vector*);
	void		*(*free)(t_vector*);
	void		(*reduce)(t_vector*);
	t_all		(*get)(t_vector*, int);
	int			len;
	char		*tab;
	int			rem;
	int			elem;
	int			type;
	int			blocksize;
};

t_vector	*new_vector(int type, int blocksize);

#endif
