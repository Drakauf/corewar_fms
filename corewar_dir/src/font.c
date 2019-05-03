/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   font.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 10:27:24 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 11:59:21 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		**load_font(void)
{
	int		fd;
	char	pixel;
	int		**font;
	int		p;
	int		f;

	if ((fd = open("fonts.txt", O_RDONLY)) == -1 ||
		!(font = (int **)malloc(sizeof(int *) * 256)))
		exit((ft_printf("\e[31;1mFont Error\e[0m\n") & 1) | 1);
	f = -1;
	while (++f < 256)
	{
		if (!(font[f] = (int *)malloc(sizeof(int) * 80)))
			exit((ft_printf("\e[31;1mMalloc Error\e[0m\n") & 1) | 1);
		p = -1;
		while (++p < 80)
		{
			read(fd, &pixel, 1);
			font[f][p] = (pixel == 'X');
			if (p % CHAR_SX == CHAR_SX - 1)
				read(fd, &pixel, 1);
		}
		read(fd, &pixel, 1);
	}
	return (font);
}
