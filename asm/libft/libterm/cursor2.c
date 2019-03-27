/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/09 04:27:12 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 04:30:25 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

void	term_move_to_line_start(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("cr", NULL));
	tputs(command, 1, term_putc);
}

void	term_save_cursor(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("sc", NULL));
	tputs(command, 1, term_putc);
}

void	term_restore_cursor(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("rc", NULL));
	tputs(command, 1, term_putc);
}

void	term_move_cursor_right_n(int n)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("Rl", NULL));
	tputs(tgoto(command, n, 0), 1, term_putc);
}

void	term_move_cursor_right(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("nd", NULL));
	tputs(command, 1, term_putc);
}
