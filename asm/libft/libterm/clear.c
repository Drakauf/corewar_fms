/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libterm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 14:40:34 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 04:30:53 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

void	term_clear(void)
{
	static char	*clear = NULL;

	if (clear == NULL)
		clear = ft_strdup(tgetstr("cl", NULL));
	tputs(clear, 1, term_putc);
}

void	term_clear_after(void)
{
	static char	*clear = NULL;

	if (clear == NULL)
		clear = ft_strdup(tgetstr("cd", NULL));
	tputs(clear, 1, term_putc);
}

void	term_clear_eol(void)
{
	static char	*clear = NULL;

	if (clear == NULL)
		clear = ft_strdup(tgetstr("ce", NULL));
	tputs(clear, 1, term_putc);
}
