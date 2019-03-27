/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libterm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/11 14:40:34 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 04:34:13 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft.h"

void	term_color_reset(void)
{
	static char	*reset = NULL;

	if (!reset)
		reset = ft_strdup(tgetstr("me", NULL));
	tputs(reset, 1, term_putc);
}

void	term_set_color(int color)
{
	int	type;

	type = color & 0xff0;
	color &= 0x00f;
	term_color_reset();
	if (type & BOLD)
		term_set_bold();
	if (type & UNDERLINE)
		term_set_underline();
	if (type & BLINK)
		term_set_blink();
	if (type & REVERSE)
		term_set_reverse();
}
