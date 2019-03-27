/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_options.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 19:15:20 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 14:11:03 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_options(t_ft_options **opt)
{
	t_ft_options	*tmp;
	t_ft_options	*o;

	if ((o = *opt) == NULL)
		return ;
	tmp = NULL;
	while (o)
	{
		tmp = o->next;
		free(o);
		o = tmp;
	}
	*opt = NULL;
}
