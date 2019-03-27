/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_options.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 18:10:43 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 15:09:51 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** get arguments from the cli
**
** format :
**	-[a-zA-Z](=.+)?
**	--[a-zA-Z][a-zA-Z_-](=.+)?
*/

static void		add_opt(t_ft_options **opt, char *a1, int c, char *a2)
{
	t_ft_options	*new;
	t_ft_options	*tmp;

	if (!(new = (t_ft_options *)malloc(sizeof(t_ft_options))))
		return ;
	new->name = a1;
	new->value = a2;
	new->sname = c;
	new->next = NULL;
	if (!*opt)
	{
		*opt = new;
		return ;
	}
	tmp = *opt;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void		add_long_opt(t_ft_options **opt, char *ptr, char *value)
{
	if (value)
	{
		ptr[value - ptr] = 0;
		add_opt(opt, ptr, 0, value + 1);
	}
	else
		add_opt(opt, ptr, 0, NULL);
}

static void		add_short_opt(t_ft_options **opt, char *ptr, char *value)
{
	if (value)
	{
		if (!ft_isalpha(*ptr) || (value - ptr) > 1)
			add_opt(opt, NULL, 0, ptr);
		else
		{
			add_opt(opt, NULL, *ptr, value + 1);
		}
		return ;
	}
	while (*ptr)
	{
		if (ft_isalpha(*ptr))
		{
			add_opt(opt, NULL, *ptr, NULL);
		}
		ptr++;
	}
}

t_ft_options	*get_cli_options(int ac, char **av)
{
	t_ft_options	*opt;
	char			*ptr;
	char			*value;

	opt = NULL;
	while (ac--)
	{
		if (**av == '-')
		{
			ptr = *av + 1;
			value = ft_strchr(ptr, '=');
			if (*ptr == '-')
			{
				ptr++;
				add_long_opt(&opt, ptr, value);
			}
			else
				add_short_opt(&opt, ptr, value);
		}
		else
			add_opt(&opt, NULL, 0, ft_strdup(*av));
		av++;
	}
	return (opt);
}
