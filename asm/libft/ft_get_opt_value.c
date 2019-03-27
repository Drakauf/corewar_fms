/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_opt_value.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 17:09:14 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 14:09:34 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_opt_value(const char *s, t_ft_options *o)
{
	const int	length = ft_strlen(s);

	while (o)
	{
		if (length > 1)
		{
			if (o->name && ft_strcmp(o->name, s) == 0)
				return (o->value);
		}
		else
		{
			if (o->sname == *s)
				return (o->value);
		}
		o = o->next;
	}
	return (NULL);
}
