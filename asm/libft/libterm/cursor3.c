/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor3.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/09 04:28:14 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 04:30:00 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

void	term_move_cursor_left(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("le", NULL));
	tputs(command, 1, term_putc);
}

void	term_move_cursor_up_n(int n)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("UP", NULL));
	tputs(tgoto(command, n, 0), 1, term_putc);
}

void	term_move_cursor_up(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("up", NULL));
	tputs(command, 1, term_putc);
}

void	term_move_cursor_down_n(int n)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("DO", NULL));
	tputs(tgoto(command, n, 0), 1, term_putc);
}

void	term_move_cursor_down(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("do", NULL));
	tputs(command, 1, term_putc);
}
