/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   screen.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 13:47:39 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 04:32:30 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

void	term_clear(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("cl", NULL));
	tputs(command, 1, term_putc);
}

void	term_clear_after(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("ce", NULL));
	tputs(command, 1, term_putc);
}

void	term_clear_before(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("cb", NULL));
	tputs(command, 1, term_putc);
}
