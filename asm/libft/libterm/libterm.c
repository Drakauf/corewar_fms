/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libterm.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 14:40:34 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 04:37:18 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

void	term_get_size(int *col, int *row)
{
	if (col)
	{
		*col = tgetnum("co");
	}
	if (row)
	{
		*row = tgetnum("li");
	}
}

int		term_putc(int c)
{
	return (write(2, &c, 1));
}

int		term_init(void)
{
	const char	*term = getenv("TERM");
	int			ret;

	if (term == NULL)
		return (-2);
	if ((ret = tgetent(NULL, term)) < 1)
		return (ret);
	return (1);
}

int		term_noecho(int stat)
{
	static int				mode = -1;
	static struct termios	default_mode;
	static struct termios	noecho_mode;

	if (mode == -1)
	{
		if (tcgetattr(0, &default_mode) == -1)
			return (-1);
		noecho_mode = default_mode;
		noecho_mode.c_lflag &= ~(ECHO | ICANON);
		noecho_mode.c_cc[VMIN] = 0;
		noecho_mode.c_cc[VTIME] = 0;
		mode = 0;
	}
	if (mode == stat)
		return (0);
	if (stat == 1)
		return (tcsetattr(0, TCSANOW, &noecho_mode));
	if (stat == 0)
		return (tcsetattr(0, TCSANOW, &default_mode));
	return (-1);
}
