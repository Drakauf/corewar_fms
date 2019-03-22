/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isset_option.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/15 17:08:28 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 14:08:50 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_isset_option(const char *s, t_ft_options *o)
{
	const int	length = ft_strlen(s);

	while (o)
	{
		if (length > 1)
		{
			if (o->name && ft_strcmp(o->name, s) == 0)
				return (1);
		}
		else
		{
			if (o->sname == *s)
				return (1);
		}
		o = o->next;
	}
	return (0);
}
