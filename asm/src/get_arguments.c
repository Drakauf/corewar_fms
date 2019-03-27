/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_arguments.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 10:33:29 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 10:45:00 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		**set_option_1(char *arg[], t_data *d)
{
	d->syntax = DFLT;
	if (ft_strcmp(*arg, "--gnu") == 0) 
		d->syntax = ATNT;
	if (ft_strcmp(*arg, "--intel") == 0) 
		d->syntax = INTL;
	if (ft_strcmp(*arg, "--clang") == 0)
	{
		ft_puts("Un jour peut-etre...\n");
		exit(0);
		d->syntax = CSTYLE;
	}
	if (d->syntax != DFLT)
		arg++;
	return (arg);
}

static int		set_option_2(char *arg[], t_data *d)
{
	if (ft_strcmp(*arg, "-o") == 0)
	{
		ft_assert(!valid_ext(d->input, "s"), EXT_ERROR);
		ft_assert(arg[1] == NULL, OUTPUT_EXPECT);
		d->output = ft_strdup(arg[1]);
		return (1);
	}
	else if (ft_strcmp(*arg, "-d") == 0)
	{
		ft_assert(!valid_ext(d->input, "cor"), EXT_ERROR);
		if (d->syntax != DFLT)
			write(2, "\e[0;33mWarning:\e[0m syntax option ignored.\n", 43);
		return (1);
	}
	return (0);
}

extern void		get_argument(char *arg[], t_data *d)
{
	d->output = NULL;
	arg = set_option_1(arg, d);
	ft_assert(*arg == NULL, FILENAME_EXPECT);
	d->input = *(arg++);
	if (*arg != NULL && set_option_2(arg, d))
		return ;
	ft_assert(!valid_ext(d->input, "s"), EXT_ERROR);
	d->output = replace_ext(d->input);
}
