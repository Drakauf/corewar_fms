/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libterm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 14:40:34 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 04:33:04 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

void	term_set_bold(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("md", NULL));
	tputs(command, 1, term_putc);
}

void	term_set_underline(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("us", NULL));
	tputs(command, 1, term_putc);
}

void	term_set_blink(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("mb", NULL));
	tputs(command, 1, term_putc);
}

void	term_set_reverse(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("mr", NULL));
	tputs(command, 1, term_putc);
}
