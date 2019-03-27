/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_options.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 18:49:17 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 14:10:43 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_options(t_ft_options *opt)
{
	int		i;

	i = 1;
	while (opt)
	{
		ft_puts("\e[1margument ");
		ft_puts(ft_itoa(i));
		ft_puts(" : \e[0m\n");
		if (opt->name)
		{
			ft_puts("name  = \"");
			ft_puts(opt->name);
			ft_puts("\"\n");
		}
		if (opt->value)
		{
			ft_puts("value = \"");
			ft_puts(opt->value);
			ft_puts("\"\n");
		}
		i++;
		opt = opt->next;
	}
}
