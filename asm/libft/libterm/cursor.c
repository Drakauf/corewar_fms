/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libterm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 14:40:34 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 04:35:56 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

void	term_move_cursor(int col, int row)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("cm", NULL));
	tputs(tgoto(command, col, row), 1, term_putc);
}

void	term_hide_cursor(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("vi", NULL));
	tputs(command, 1, term_putc);
}

void	term_display_cursor(void)
{
	static char	*command = NULL;

	if (command == NULL)
		command = ft_strdup(tgetstr("ve", NULL));
	tputs(command, 1, term_putc);
}

void	term_get_cursor(int *col, int *row)
{
	char	*x;
	char	*y;
	int		i;
	char	buf[11];

	term_noecho(1);
	write(1, "\e[6n", 4);
	i = read(0, buf, 10);
	term_noecho(0);
	buf[i] = 0;
	y = buf + 2;
	i -= 2;
	buf[i + 1] = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
		i--;
	x = buf + i + 1;
	*col = ft_atoi(x);
	*row = ft_atoi(y);
}
